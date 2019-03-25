#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nRet, nMin, n;
int nFiled[101][101];
int nvisit[101][101];

int dirx[] = { 0, 0, 1, -1 };
int diry[] = { 1, -1, 0, 0 };

typedef struct pos{
	int x, y;
};

typedef struct inf{
	int x, y, cnt;
};

vector<vector<pos>> island_v;

void island(int crtx, int crty, int _index)
{
	nvisit[crty][crtx] = 1;
	nFiled[crty][crtx] = _index;
	queue <pos> island_q;
	vector <pos> temp_v;
	temp_v.push_back({ crtx, crty });
	island_q.push({ crtx, crty });

	int x, y, nextx, nexty;
	while (!island_q.empty()){
		x = island_q.front().x;
		y = island_q.front().y;
		island_q.pop();

		for (int i = 0; i < 4; i++){
			nextx = x + dirx[i];
			nexty = y + diry[i];

			if (nFiled[nexty][nextx] && nextx >= 0 && nextx < n && nexty >= 0 && nexty < n
				&& !nvisit[nexty][nextx]){
				island_q.push({ nextx, nexty });
				nvisit[nexty][nextx] = 1;
				nFiled[nexty][nextx] = _index;
				temp_v.push_back({ nextx, nexty });
			}
		}
	}
	if(!temp_v.empty())
		island_v.push_back(temp_v);
}

void bfs(int crtx, int crty, int crt_island){

	nvisit[crty][crtx] = 1;
	queue <inf> q;
	q.push({ crtx, crty, 0 });

	inf crt_p;
	while (!q.empty()){
		crt_p = q.front();
		q.pop();

		if (nRet <= crt_p.cnt)
			continue;

		if (nFiled[crt_p.y][crt_p.x] != crt_island && nFiled[crt_p.y][crt_p.x]){
			nRet = crt_p.cnt;
		}


		inf next_p;
		for (int i = 0; i < 4; i++){
			next_p.x = crt_p.x + dirx[i];
			next_p.y = crt_p.y + diry[i];

			if (nFiled[next_p.y][next_p.x] != crt_island
				&& next_p.x >= 0 && next_p.x < n && next_p.y >= 0 && next_p.y < n
				&& !nvisit[next_p.y][next_p.x]){
				next_p.cnt = crt_p.cnt + 1;
				nvisit[next_p.y][next_p.x] = 1;
				q.push(next_p);
			}
		}
	}
}


int main()
{
	freopen("sample_input.txt", "r", stdin);

	scanf("%d", &n);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			nvisit[i][j] = 0;
			scanf("%d", &nFiled[i][j]);
		}
	}
	
	int index = 0;
	island_v.clear();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (nFiled[i][j] && !nvisit[i][j]){
				index++;
				island(j, i, index);
			}
		}
	}

	nMin = 100001;
	for (int i = 0; i < island_v.size(); i++){
		for (int j = 0; j < island_v[i].size(); j++){
			pos crt_pos = island_v[i][j];
			nRet = 100000;

			for (int i = 0; i < n; i++){
				for (int j = 0; j < n; j++){
					nvisit[i][j] = 0;
				}
			}

			bfs(crt_pos.x, crt_pos.y, nFiled[crt_pos.y][crt_pos.x]);

			if (nMin > nRet)
				nMin = nRet;
		}
	}
	printf("%d\n", nMin - 1);


	return 0;

}