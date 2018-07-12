//
//  matrix_binary.inl
//  megranate
//
//  Created by liu on 2018/7/8.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef matrix_binary_inl
#define matrix_binary_inl

namespace megranate {

    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator= (MgMatrix<T, M, N> const& other){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = other._m[line][col];
            }
        }
        return *this;
    }
    
    
    TEMPLARE_MG_MATRIX
    bool MgMatrix<T, M, N, AP, AT>::operator== (MgMatrix<T, M, N> const& other){
        bool rt = true;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                if (!AP::equal(_m[line][col], other._m[line][col])){
                    rt = false;
                    break;
                }
            }
        }
        return rt;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator+ (MgMatrix<T, M, N> const& other) const{
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::add(_m[line][col], other._m[line][col]);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator- (MgMatrix<T, M, N> const& other) const{
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::sub(_m[line][col], other._m[line][col]);
            }
        }
        return temp;
    }
    

    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator* (MgMatrix<T, M, N> const& other) const{
        assert(M == N);
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                for(unsigned int i = 0; i < M; i++){
                    temp._m[line][col] += AP::ride(_m[line][i], other._m[i][col]);
                }
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator/ (MgMatrix<T, M, N> const& other) const{
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::divide(_m[line][col], other._m[line][col]);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator% (MgMatrix<T, M, N> const& other) const{
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::mod(_m[line][col], other._m[line][col]);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator+ (T const& t){
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::add(_m[line][col], t);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator- (T const& t){
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::sub(_m[line][col], t);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator* (T const& t){
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::ride(_m[line][col], t);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator/ (T const& t){
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::divide(_m[line][col], t);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::operator% (T const& t){
        MgMatrix<T, M, N> temp;
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                temp._m[line][col] = AP::mod(_m[line][col], t);
            }
        }
        return temp;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator+= (MgMatrix<T, M, N> const& other){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::add(_m[line][col], other._m[line][col]);
            }
        }
        return *this;
    }

    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator-= (MgMatrix<T, M, N> const& other){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::sub(_m[line][col], other._m[line][col]);
            }
        }
        return *this;
    }

    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator*= (MgMatrix<T, M, N> const& other){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::ride(_m[line][col], other._m[line][col]);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator/= (MgMatrix<T, M, N> const& other){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::divide(_m[line][col], other._m[line][col]);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator%= (MgMatrix<T, M, N> const& other){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::mod(_m[line][col], other._m[line][col]);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator+= (T const& t){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::add(_m[line][col], t);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator-= (T const& t){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::sub(_m[line][col], t);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator*= (T const& t){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::ride(_m[line][col], t);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator/= (T const& t){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::divide(_m[line][col], t);
            }
        }
        return *this;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>& MgMatrix<T, M, N, AP, AT>::operator%= (T const& t){
        for (unsigned int line = 0; line < M; line++) {
            for (unsigned int col = 0; col < N; col++) {
                _m[line][col] = AP::mod(_m[line][col], t);
            }
        }
        return *this;
    }

}

#endif /* matrix_binary_inl */
