#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int N, M;
vector<pair<int, int>> houses;   // 집의 위치
vector<pair<int, int>> chicken;  // 치킨집의 위치
vector<pair<int, int>> selected_chicken;  // 선택된 치킨집들의 위치
int result = INT_MAX;  // 최소 거리의 합

// 두 점 사이의 거리 계산
int getDistance(pair<int, int>& a, pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

// 치킨집의 조합을 구하는 함수
void chooseChicken(int idx, int count) {
    if (count == M) {
        int city_chicken_dist = 0;

        // 모든 집에 대해 가장 가까운 치킨집의 거리 합 계산
        for (auto& house : houses) {
            int min_dist = INT_MAX;
            // 선택된 치킨집 중에서 가장 가까운 치킨집 찾기
            for (auto& chicken_place : selected_chicken) {
                min_dist = min(min_dist, getDistance(house, chicken_place));
            }
            city_chicken_dist += min_dist;
        }

        // 최소 거리 합 업데이트
        result = min(result, city_chicken_dist);
        return;
    }

    // 현재 인덱스부터 치킨집을 하나씩 선택해가며 조합 생성
    for (int i = idx; i < chicken.size(); i++) {
        selected_chicken.push_back(chicken[i]);
        chooseChicken(i + 1, count + 1);
        selected_chicken.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    // 도시의 정보 입력 받기
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int value;
            cin >> value;
            if (value == 1) {
                houses.push_back({ i, j });  // 집 위치
            }
            else if (value == 2) {
                chicken.push_back({ i, j }); // 치킨집 위치
            }
        }
    }

    // 치킨집 선택 조합 구하기
    chooseChicken(0, 0);

    cout << result << "\n";

    return 0;
}
