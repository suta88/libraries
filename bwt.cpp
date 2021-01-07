#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

struct SA_IS{
    std::vector<int> sa;
    std::vector<int> lcp;

    SA_IS(std::string str){
        str += '$';
        int n = str.size();
        std::vector<int> s(n);
        for(int i=0; i<n; i++) s[i] = str[i] - '$';
        sa = sa_is(s, 100);
        lcp.resize(n);
        make_lcp(str);
    }

    SA_IS(vector<int> str, int k){
        str.push_back(0);
        int n = str.size();
        sa = sa_is(str, k);
    }

    void induced_sort(std::vector<int> &sa, std::vector<int> &s, std::vector<int> &lms, std::string &ls, int k){
        int n = s.size();
        std::vector<int> c_size(k,0), bin(k+1,0), count(k,0);
        for(int i=0; i<n; i++){
            c_size[s[i]]++;
        }
        for(int i=0; i<k; i++){
            bin[i+1] = bin[i] + c_size[i];
        }

        for(int i=lms.size()-1; i>=0; i--){
            int id = s[lms[i]];
            sa[bin[id+1] - 1 - count[id]] = lms[i];
            count[id]++;
        }
        
        //L-sort
        std::fill(count.begin(), count.end(), 0);
        for(int i=0; i<n; i++){
            if(sa[i] == -1) continue;
            int next = sa[i] - 1;
            if(next == -1 || ls[next] == 'S') continue;
            int id = s[next];
            sa[bin[id] + count[id]] = next;
            count[id]++;
            if(i > 0 && ls[sa[i]] == 'S' && ls[sa[i]-1] == 'L') sa[i] = -1;
        }

        //S-sort
        std::fill(count.begin(), count.end(), 0);
        for(int i=n-1; i>=0; i--){
            if(sa[i] == -1) continue;
            int next = sa[i] - 1;
            if(next == -1 || ls[next] == 'L') continue;
            int id = s[next];
            sa[bin[id+1] - 1 - count[id]] = next;
            count[id]++;
        }
    }

    std::vector<int> sa_is(std::vector<int> &s, int k){
        int n = s.size();
        std::vector<int> sa(n,-1);
        std::vector<bool> is_lms(n,false);
        std::string ls;
        ls.resize(n);
        ls[n-1] = 'S';
        for(int i=n-2; i>=0; i--){
            if(s[i] < s[i+1]) ls[i] = 'S';
            else if(s[i] > s[i+1]) ls[i] = 'L';
            else ls[i] = ls[i+1];
        }
        std::vector<int> lms, sorted_lms;
        for(int i=0; i<n-1; i++){
            if(ls[i] == 'L' && ls[i+1] == 'S'){
                lms.push_back(i+1);
                is_lms[i+1] = true;
            }
        }
        
        //1回目のinduced_sortでlms-substringが辞書順にソートされる
        induced_sort(sa,s,lms,ls,k);

        for(int i=0; i<n; i++){
            if(is_lms[sa[i]]){
                sorted_lms.push_back(sa[i]);
            }
            sa[i] = -1;
        }

        sa[sorted_lms[0]] = 0;
        int kind = 0;
        for(int i=0; i<sorted_lms.size()-1; i++){
            bool same = true;
            int x = sorted_lms[i];
            int y = sorted_lms[i+1];
            int d = 0;
            while(1){
                if(x+d == n || y+d == n){
                    if(x+d == n){
                        if(!is_lms[y+d]) same = false; 
                    }else{
                        if(!is_lms[x+d]) same = false;
                    }
                    break;
                }
                if(d > 0 && (is_lms[x+d] || is_lms[y+d])){
                    if(is_lms[x+d] != is_lms[y+d]) same = false;
                    break;
                }
                if(s[x+d] != s[y+d]){
                    same = false;
                    break;
                }
                d++;
            }
            if(!same) kind++;
            sa[sorted_lms[i+1]] = kind;
        }

        std::vector<int> new_str;
        for(int i=0; i<n; i++){
            if(is_lms[i]){
                new_str.push_back(sa[i]);
                sa[i] = -1;
            }
        }

        vector<int> new_lms(lms.size());
        if(kind + 1 == lms.size()){
            new_lms = sorted_lms;
        }else{
            sorted_lms = sa_is(new_str, kind + 1);
            for(int i=0; i<sorted_lms.size(); i++){
                new_lms[i] = lms[sorted_lms[i]];
            }
        }
        
        induced_sort(sa,s,new_lms,ls,k);
        return sa;
    }

    void make_lcp(string &s){
        s.pop_back();
        int n = s.size();
        vector<int> ran(n+1);
        for(int i=0; i<=n; i++) ran[sa[i]] = i;
        
        int h = 0;
        lcp[0] = 0;
        for(int i=0; i<n; i++){
            int j = sa[ran[i]-1];
            if(h > 0) h--;
            for(; j+h<n && i+h<n; h++){
                if(s[j+h] != s[i+h]) break;
            }
            lcp[ran[i]-1] = h;
        }
    }
};

std::string bwt(std::vector<int> &sa, std::string &s){
	std::string b;
	int n = sa.size();
	b.resize(n);
	for(int i=0; i<n; i++){
		if(sa[i] == 0) b[i] = '$';
		else b[i] = s[sa[i]-1];
	}
	return b;
}

int main(){
	string s; cin >> s;
	SA_IS sa(s);
    cout << bwt(sa.sa,s) << "\n";
}