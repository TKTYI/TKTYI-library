using ll = long long;
using pt = pair<int, ll>;
struct CH {
    using pt = pair<int, ll>;
    vector<pt> points;
    vector<ll> slopes;
    CH pointwise_sum(CH p, CH q) {
        vector<int> x_card;
        for (int cp = 0, cq = 0; cp < (int)p.points.size() || cq < (int)q.points.size();) {
            if (cq == (int)q.points.size()) x_card.emplace_back(p.points[cp++].first);
            else if (cp == (int)p.points.size()) x_card.emplace_back(q.points[cq++].first);
            else if (p.points[cp].first < q.points[cq].first) x_card.emplace_back(p.points[cp++].first);
            else if (q.points[cq].first < p.points[cp].first) x_card.emplace_back(q.points[cq++].first);
            else x_card.emplace_back(p.points[cp++].first), cq++;
        }
        CH res;
        int cp = 0, cq = 0;
        for (int i = 0; i < (int)x_card.size(); i++) {
            int x = x_card[i];
            while (cp + 1 < (int)p.points.size() && p.points[cp + 1].first <= x) cp++;
            while (cq + 1 < (int)q.points.size() && q.points[cq + 1].first <= x) cq++;
            ll yp = p.points[cp].second - p.slopes[cp] * (x - p.points[cp].first);
            ll yq = q.points[cq].second - q.slopes[cq] * (x - q.points[cq].first);
            if (res.slopes.empty() || res.slopes.back() != p.slopes[cp] + q.slopes[cq]) {
                res.points.emplace_back(pt(x, yp + yq));
                res.slopes.emplace_back(p.slopes[cp] + q.slopes[cq]);
            }
 
        }
        return res;
    }
    CH pointwise_max(CH p, CH q) {
        vector<int> x_card;
        for (int cp = 0, cq = 0; cp < (int)p.points.size() || cq < (int)q.points.size();) {
            if (cq == (int)q.points.size()) x_card.emplace_back(p.points[cp++].first);
            else if (cp == (int)p.points.size()) x_card.emplace_back(q.points[cq++].first);
            else if (p.points[cp].first < q.points[cq].first) x_card.emplace_back(p.points[cp++].first);
            else if (q.points[cq].first < p.points[cp].first) x_card.emplace_back(q.points[cq++].first);
            else x_card.emplace_back(p.points[cp++].first), cq++;
        }
        CH res;
        int cp = 0, cq = 0;
        for (int i = 0; i < (int)x_card.size(); i++) {
            int x = x_card[i];
            int x_next = (i + 1 == (int)x_card.size() ? 1000000 : x_card[i + 1] - 1);
            while (cp + 1 < (int)p.points.size() && p.points[cp + 1].first <= x) cp++;
            while (cq + 1 < (int)q.points.size() && q.points[cq + 1].first <= x) cq++;
            ll yp = p.points[cp].second - p.slopes[cp] * (x - p.points[cp].first);
            ll yq = q.points[cq].second - q.slopes[cq] * (x - q.points[cq].first);
            ll yp_next = p.points[cp].second - p.slopes[cp] * (x_next - p.points[cp].first);
            ll yq_next = q.points[cq].second - q.slopes[cq] * (x_next - q.points[cq].first);
            if (yp > yq || (yp == yq && p.slopes[cp] < q.slopes[cq])) {
                if (res.slopes.empty() || res.slopes.back() != p.slopes[cp]) {
                    res.points.emplace_back(pt(x, yp));
                    res.slopes.emplace_back(p.slopes[cp]);
                }
                if (yp_next < yq_next && (res.slopes.empty() || res.slopes.back() != q.slopes[cq])) {
                    int x_int = x + 1 + (yp - yq - 1) / (p.slopes[cp] - q.slopes[cq]);
                    res.points.emplace_back(pt(x_int, q.points[cq].second - q.slopes[cq] * (x_int - q.points[cq].first)));
                    res.slopes.emplace_back(q.slopes[cq]);
                }
            }
            else {
                if (res.slopes.empty() || res.slopes.back() != q.slopes[cq]) {
                    res.points.emplace_back(pt(x, yq));
                    res.slopes.emplace_back(q.slopes[cq]);
                }
                if (yp_next > yq_next && (res.slopes.empty() || res.slopes.back() != p.slopes[cp])) {
                    int x_int = x + 1 + (yq - yp - 1) / (q.slopes[cq] - p.slopes[cp]);
                    res.points.emplace_back(pt(x_int, p.points[cp].second - p.slopes[cp] * (x_int - p.points[cp].first)));
                    res.slopes.emplace_back(p.slopes[cp]);
                }
            }
        }
        return res;
    }
};