#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e7 + 1;
vector<int> smallest_factor(maxn, 0);
vector<int8_t> smallest_power(maxn, 0);
vector<int8_t> mobius(maxn, 0);
vector<int> totient(maxn, 0);
vector<bool> prime(maxn, true);
vector<int> primes;

void init() {
    // linear sieve
    mobius[1] = 1;
    totient[1] = 1;
    prime[0] = false;
    prime[1] = false;

    for (int i = 2; i <= maxn; i++) {
        if (prime[i]) {
            smallest_factor[i] = i;
            smallest_power[i] = 1;
            mobius[i] = -1;
            totient[i] = i - 1;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > smallest_factor[i] || i * p > maxn)
                break;

            prime[i * p] = false;
            smallest_factor[i * p] = p;
            bool smallest_factor_i_p = (smallest_factor[i] == p);
            smallest_power[i * p] = 1 + smallest_power[i] * smallest_factor_i_p;
            mobius[i * p] = (-mobius[i]) * (!smallest_factor_i_p);
            totient[i * p] = (p - (!smallest_factor_i_p)) * totient[i];
        }
    }
}

vector<pair<int, int>> prime_factorize(int n) {
    vector<pair<int, int>> result;

    while (n != 1) {
        int p = smallest_factor[n];
        int cnt = 0;

        do {
            n /= p;
            cnt++;
        } while (n % p == 0);

        result.emplace_back(p, cnt);
    }

    return result;
}

vector<int> generate_factors(int n) {
    vector<pair<int, int>> prime_factors = prime_factorize(n);
    int count = 1;

    for (auto pf : prime_factors)
        count *= pf.second + 1;

    vector<int> factors(1, 1);
    factors.reserve(count);

    for (auto pf : prime_factors) {
        int p = pf.first;
        int power = pf.second;
        int before_size = factors.size();

        for (int i = 0; i < power * before_size; i++)
            factors.push_back(factors[factors.size() - before_size] * p);
    }

    return factors;
}
