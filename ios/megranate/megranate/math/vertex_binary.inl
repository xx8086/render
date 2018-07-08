//
//  vertex_binary.inl
//  megranate
//
//  Created by liu on 2018/7/5.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef vertex_binary_inl
#define vertex_binary_inl

namespace megranate {
  
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator= (MgVertex<T, N> const& other){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = other._datas[i];
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    bool MgVertex<T, N, AP, AT>::operator== (MgVertex<T, N> const& other){
        bool rt = true;
        for (unsigned int i = 0; i < N; i++) {
            if(!AP::equal(TraitsN<T, N>::_datas[i], other._datas[i])){
                rt = false;
                break;
            }
        }
        return rt;
    }
    
    
    ///-----
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator+ (MgVertex<T, N> const& other){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::add(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator- (MgVertex<T, N> const& other){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::sub(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator* (MgVertex<T, N> const& other){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::ride(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator/ (MgVertex<T, N> const& other){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::divide(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator% (MgVertex<T, N> const& other){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::mod(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator+ (T const& t){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::add(TraitsN<T, N>::_datas[i], t);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator- (T const& t){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::sub(TraitsN<T, N>::_datas[i], t);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator* (T const& t){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::ride(TraitsN<T, N>::_datas[i], t);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator/ (T const& t){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::divide(TraitsN<T, N>::_datas[i], t);
        }
        return temp;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N> MgVertex<T, N, AP, AT>::operator% (T const& t){
        MgVertex<T, N> temp;
        for (unsigned int i = 0; i < N; i++) {
            temp._datas[i] = AP::mod(TraitsN<T, N>::_datas[i], t);
        }
        return temp;
    }

    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator+= (MgVertex<T, N> const& other){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::add(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator-= (MgVertex<T, N> const& other){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::sub(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator*= (MgVertex<T, N> const& other){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::ride(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return *this;
    }

    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator/= (MgVertex<T, N> const& other){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::divide(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator%= (MgVertex<T, N> const& other){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::mod(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return *this;
    }

    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator+ (T const& t){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::add(TraitsN<T, N>::_datas[i], t);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator- (T const& t){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::sub(TraitsN<T, N>::_datas[i], t);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator* (T const& t){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::ride(TraitsN<T, N>::_datas[i], t);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator/ (T const& t){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::divide(TraitsN<T, N>::_datas[i], t);
        }
        return *this;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N>& MgVertex<T, N, AP, AT>::operator% (T const& t){
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AP::mod(TraitsN<T, N>::_datas[i], t);
        }
        return *this;
    }
}

#endif /* vertex_binary_inl */
