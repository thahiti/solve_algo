#include <stdio.h>
#include <string.h>
#include <algorithm>

const int _max = 12345678;
using namespace std;

char ans[300001];
char minans[300001];
int minlv;

void solve(int a, int b, int lv){
	for(;;lv++){
		if(a==1 && b==1){
			if(minlv > lv){
				minlv = lv;
				ans[lv] = 0;
				strcpy(minans, ans);
			}
			break;
		}
		if(a==0 || b==0){
			break;
		}
		if(a>b){
			a = a-b;
			ans[lv] = 'R';
		}else{
			b = b-a;
			ans[lv] = 'B';
		}
	}
}

//count for each case, do not care actual choices
int pre_solve(int a, int b){
	//base case1, wrong case can't go to 1,1
	if(a==0 || b==0)
		return 300001;

	//base case2, reach to answer, no more operation needed
	if(a==1 && b==1)
		return 1;

	//fix big number, small number
	int big = max(a, b);
	int small = min(a, b);

	//if small is 1, it takes big-1 operation
	if(small == 1)
		return big-1;

	//divide & modular can reduce calculation
	//ex) case(19,3) -> 16,3 -> 13,3 -> 10,3 -> 7,3 -> 4,3 -> 1,3
	//19,3 = 6*3+1 -> 6 operation + case(1,3)
	int div = big/small;
	int mod = big%small;
	return div + pre_solve(mod, small);
}

int main(){
    int T;
    scanf(" %d", &T);
    for(int i=0; i<T; ++i){
        int N;
		minlv = 300001;

        scanf(" %d", &N);
		if(0 == N || 1 == N){
			printf("\n");
			continue;
		}

		int pre_min = 300001;
		int pre_i = 0;
        for(int i=1; i<N/2+1; ++i){
            int lv = pre_solve(i, N-i);
			if(lv >= pre_min)
				continue;
			pre_min = lv;
			pre_i = i;
        }

		ans[0] = 'R';
		solve(pre_i, N-pre_i, 1);
		for(int i=minlv-1; i>=0; --i)
			printf("%c", minans[i]);
		printf("\n");
    }
	return 0;
}


