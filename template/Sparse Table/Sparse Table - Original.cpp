/* 
    Template created by Alexandru Olteanu {AlexandruINV}
*/
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Sparse%20Table/Sparse%20Table%20-%20Original.cpp
template<typename A>
struct SparseTable{
    
    vector<vector<A>> matrix;
    vector<A> array;
    vector<A> log_values;
    
    SparseTable(int n){
        int max_log = 0, power = 1;
        while(power <= n){
            power <<= 1;
            ++max_log;
        }
        array.resize(n + 1);
        log_values.resize(n + 1);
        matrix.resize(n + 1);
        for(int i = 1; i <= n; ++i){
            matrix[i].resize(max_log);
        }
    }
    A func(A a, A b){
        return min(a, b);//Probably it needs changes
    }
    
    void build(int l, int r){
        int max_log = 0, power = 1;
        int n = r - l + 1;
        while(power <= n){
            power <<= 1;
            ++max_log;
        }
        int number = 0;
        power = 1;
        for(int i = 1; i <= n; ++i){
            while(power <= i){
                power <<= 1;
                ++number;
            }
            power >>= 1;
            --number;
            log_values[i] = number;
        }
        for(int j = 0; j < max_log; ++j){
            for(int i = l; i <= r - (1 << j) + 1; ++i){
                if(j == 0){
                    matrix[i][j] = array[i];
                    continue;
                }
                matrix[i][j] = func(matrix[i][j - 1], matrix[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll get(A start, A finish){
        ll distance = finish - start + 1;
        ll biggest_power = log_values[distance];
        return func(matrix[start][biggest_power], matrix[finish - (1 << biggest_power) + 1][biggest_power]);
    }
};
