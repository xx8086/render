//
//  matrix_specialization.inl
//  megranate
//
//  Created by liu on 2018/7/10.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef matrix_specialization_inl
#define matrix_specialization_inl
namespace megranate {
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::inverse() const{
        assert(false);//, "MgMatrix::inverse");
        return MgMatrix<T, M, N>();
    }
    
    TEMPLARE_MG_MATRIX
    void MgMatrix<T, M, N, AP, AT>::sacled(MgVertex<T, N> const & v) const{
        static_assert(M == N, "MgMatrix::sacled_ M != N");
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                _m[i][j] *= v._datas[j];
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    void MgMatrix<T, M, N, AP, AT>::set_rotation(MgVertex<T, N> const & v) const{
        static_assert(M == N, "MgMatrix::set_rotation M != N");
        for(int i = 0; i < N; i++){
                _m[i][i] = v._datas[i];
            }
        }

    TEMPLARE_MG_MATRIX
    void MgMatrix<T, M, N, AP, AT>::set_translation(MgVertex<T, N> const & v) const{
        //static_assert(M == N, "MgMatrix::set_translation M != N");
        int n = N - 1;
        for(int i = 0; i < n; i++){
            _m[i][n] = v._datas[i];
        }
    }
    
    template<>
    MgMatrix<float, 3, 3> MgMatrix<float, 3, 3>::inverse() const{
        float det =
        m[0][0] * m[1][1] * m[2][2] +
        m[1][0] * m[2][1] * m[0][2] +
        m[2][0] * m[0][1] * m[1][2] -
        m[2][0] * m[1][1] * m[0][2] -
        m[1][0] * m[0][1] * m[2][2] -
        m[0][0] * m[2][1] * m[1][2];
        float invdet = 1.0f / det;
        return MgMatrix<float, 3, 3>(
                                     (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet,
                                     -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invdet,
                                     (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invdet,
                                     -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invdet,
                                     (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invdet,
                                     -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invdet,
                                     (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet,
                                     -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invdet,
                                     (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet
                                     );
    }
    
    template<>
    MgMatrix<float, 3, 4> MgMatrix<float, 3, 4>::inverse() const{
        float det =
        m[0][0] * m[1][1] * m[2][2] +
        m[1][0] * m[2][1] * m[0][2] +
        m[2][0] * m[0][1] * m[1][2] -
        m[2][0] * m[1][1] * m[0][2] -
        m[1][0] * m[0][1] * m[2][2] -
        m[0][0] * m[2][1] * m[1][2];
        
        float invdet = 1.0f / det;
        MgMatrix<float, 3, 4> ret;
        ret.m[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
        ret.m[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invdet;
        ret.m[0][2] = (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invdet;
        ret.m[0][3] = -(m[0][3] * ret.m[0][0] + m[1][3] * ret.m[0][1] + m[2][3] * ret.m[0][2]);
        ret.m[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invdet;
        ret.m[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invdet;
        ret.m[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invdet;
        ret.m[1][3] = -(m[0][3] * ret.m[1][0] + m[1][3] * ret.m[1][1] + m[2][3] * ret.m[1][2]);
        ret.m[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
        ret.m[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invdet;
        ret.m[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;
        ret.m[2][3] = -(m[0][3] * ret.m[2][0] + m[1][3] * ret.m[2][1] + m[2][3] * ret.m[2][2]);
        return ret;
    }
    
    template<>
    MgMatrix<float, 4, 4> MgMatrix<float, 4,4>::inverse() const{
        float v0 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
        float v1 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
        float v2 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
        float v3 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
        float v4 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
        float v5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
        
        float i00 = (v5 * m[1][1] - v4 * m[1][2] + v3 * m[1][3]);
        float i10 = -(v5 * m[1][0] - v2 * m[1][2] + v1 * m[1][3]);
        float i20 = (v4 * m[1][0] - v2 * m[1][1] + v0 * m[1][3]);
        float i30 = -(v3 * m[1][0] - v1 * m[1][1] + v0 * m[1][2]);
        
        float indet = 1.0f / (i00 * m[0][0] + i10 * m[0][1] + i20 * m[0][2] + i30 * m[0][3]);
        
        i00 *= indet;
        i10 *= indet;
        i20 *= indet;
        i30 *= indet;
        
        float i01 = -(v5 * m[0][1] - v4 * m[0][2] + v3 * m[0][3]) * indet;
        float i11 = (v5 * m[0][0] - v2 * m[0][2] + v1 * m[0][3]) * indet;
        float i21 = -(v4 * m[0][0] - v2 * m[0][1] + v0 * m[0][3]) * indet;
        float i31 = (v3 * m[0][0] - v1 * m[0][1] + v0 * m[0][2]) * indet;
        
        v0 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
        v1 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
        v2 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
        v3 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
        v4 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
        v5 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
        
        float i02 = (v5 * m[0][1] - v4 * m[0][2] + v3 * m[0][3]) * indet;
        float i12 = -(v5 * m[0][0] - v2 * m[0][2] + v1 * m[0][3]) * indet;
        float i22 = (v4 * m[0][0] - v2 * m[0][1] + v0 * m[0][3]) * indet;
        float i32 = -(v3 * m[0][0] - v1 * m[0][1] + v0 * m[0][2]) * indet;
        
        v0 = m[2][1] * m[1][0] - m[2][0] * m[1][1];
        v1 = m[2][2] * m[1][0] - m[2][0] * m[1][2];
        v2 = m[2][3] * m[1][0] - m[2][0] * m[1][3];
        v3 = m[2][2] * m[1][1] - m[2][1] * m[1][2];
        v4 = m[2][3] * m[1][1] - m[2][1] * m[1][3];
        v5 = m[2][3] * m[1][2] - m[2][2] * m[1][3];
        
        float i03 = -(v5 * m[0][1] - v4 * m[0][2] + v3 * m[0][3]) * indet;
        float i13 = (v5 * m[0][0] - v2 * m[0][2] + v1 * m[0][3]) * indet;
        float i23 = -(v4 * m[0][0] - v2 * m[0][1] + v0 * m[0][3]) * indet;
        float i33 = (v3 * m[0][0] - v1 * m[0][1] + v0 * m[0][2]) * indet;
        
        return MgMatrix<float, 4, 4>(
                                     i00, i01, i02, i03,
                                     i10, i11, i12, i13,
                                     i20, i21, i22, i23,
                                     i30, i31, i32, i33);
    }
    
}

#endif /* matrix_specialization_inl */
