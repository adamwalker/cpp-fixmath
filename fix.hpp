#include <csetjmp>
#include <fix16.h>
#include <cmath>

/*
 * Doubles and Floats
 */
template <class T>
T get_zero();

template <> float get_zero(){
    return 0;
}

template <> double get_zero(){
    return 0;
}

/*
 * Non saturating arithmetic
 */
class fix16 {
    public:
    fix16_t val;
    fix16(){
        val = 0;
    }
    fix16(int x){
        val = fix16_from_int(x);
    }
    fix16(float x){
        val = fix16_from_float(x);
    }
    fix16(double x){
        val = fix16_from_dbl(x);
    }
};

template <> fix16 get_zero(){
    fix16 ret;
    ret.val = 0;
    return ret;
}

fix16 operator+(fix16 x, fix16 y){
    fix16 ret;
    ret.val = fix16_add(x.val, y.val);
    return ret;
}

void operator+=(fix16 &x, fix16 y){
    x = x + y;
}

fix16 operator-(fix16 x, fix16 y){
    fix16 ret;
    ret.val = fix16_sub(x.val, y.val);
    return ret;
}

fix16 operator-(fix16 x){
    fix16 ret;
    ret.val = -x.val;
    return ret;
}

fix16 operator*(fix16 x, fix16 y){
    fix16 ret;
    ret.val = fix16_mul(x.val, y.val);
    return ret;
}

fix16 operator/(fix16 x, fix16 y){
    fix16 ret;
    ret.val = fix16_div(x.val, y.val);
    return ret;
}

fix16 sqrt(fix16 x){
    fix16 ret;
    ret.val = fix16_sqrt(x.val);
    return ret;
}

fix16 sin(fix16 x){
    fix16 ret;
    ret.val = fix16_sin(x.val);
    return ret;
}

fix16 cos(fix16 x){
    fix16 ret;
    ret.val = fix16_cos(x.val);
    return ret;
}

/*
 * Saturating arithmetic
 */
class fix16Sat {
    public:
    fix16_t val;
    fix16Sat(){
        val = 0;
    }
    fix16Sat(int x){
        val = fix16_from_int(x);
    }
    fix16Sat(float x){
        val = fix16_from_float(x);
    }
    fix16Sat(double x){
        val = fix16_from_dbl(x);
    }
};

template <> fix16Sat get_zero(){
    fix16Sat ret;
    ret.val = 0;
    return ret;
}

fix16Sat operator+(fix16Sat x, fix16Sat y){
    fix16Sat ret;
    ret.val = fix16_sadd(x.val, y.val);
    return ret;
}

void operator+=(fix16Sat &x, fix16Sat y){
    x = x + y;
}

fix16Sat operator-(fix16Sat x, fix16Sat y){
    fix16Sat ret;
    ret.val = fix16_ssub(x.val, y.val);
    return ret;
}

fix16Sat operator-(fix16Sat x){
    fix16Sat ret;
    ret.val = -x.val;
    return ret;
}

fix16Sat operator*(fix16Sat x, fix16Sat y){
    fix16Sat ret;
    ret.val = fix16_smul(x.val, y.val);
    return ret;
}

fix16Sat operator/(fix16Sat x, fix16Sat y){
    fix16Sat ret;
    ret.val = fix16_sdiv(x.val, y.val);
    return ret;
}

fix16Sat sqrt(fix16Sat x){
    fix16Sat ret;
    ret.val = fix16_sqrt(x.val);
    return ret;
}

fix16Sat sin(fix16Sat x){
    fix16Sat ret;
    ret.val = fix16_sin(x.val);
    return ret;
}

fix16Sat cos(fix16Sat x){
    fix16Sat ret;
    ret.val = fix16_cos(x.val);
    return ret;
}

/*
 * Exception throwing arithmetic
 */
jmp_buf overflow_exc;

class fix16Exc {
    public:
    fix16_t val;
    fix16Exc(){
        val = 0;
    }
    fix16Exc(int x){
        val = fix16_from_int(x);
    }
    fix16Exc(float x){
        val = fix16_from_float(x);
    }
    fix16Exc(double x){
        val = fix16_from_dbl(x);
    }
};

template <> fix16Exc get_zero(){
    fix16Exc ret;
    ret.val = 0;
    return ret;
}

fix16Exc operator+(fix16Exc x, fix16Exc y){
    fix16Exc ret;
    ret.val = fix16_add(x.val, y.val);

    if(ret.val == fix16_overflow){
        longjmp(overflow_exc, 1);
    }
    return ret;
}

void operator+=(fix16Exc &x, fix16Exc y){
    x = x + y;
}

fix16Exc operator-(fix16Exc x, fix16Exc y){
    fix16Exc ret;
    ret.val = fix16_sub(x.val, y.val);
    if(ret.val == fix16_overflow){
        longjmp(overflow_exc, 1);
    }
    return ret;
}

fix16Exc operator-(fix16Exc x){
    fix16Exc ret;
    ret.val = -x.val;
    return ret;
}

fix16Exc operator*(fix16Exc x, fix16Exc y){
    fix16Exc ret;
    ret.val = fix16_mul(x.val, y.val);
    if(ret.val == fix16_overflow){
        longjmp(overflow_exc, 1);
    }
    return ret;
}

fix16Exc operator/(fix16Exc x, fix16Exc y){
    fix16Exc ret;
    ret.val = fix16_div(x.val, y.val);
    if(ret.val == fix16_overflow){
        longjmp(overflow_exc, 1);
    }
    return ret;
}

fix16Exc sqrt(fix16Exc x){
    fix16Exc ret;
    ret.val = fix16_sqrt(x.val);
    return ret;
}

fix16Exc sin(fix16Exc x){
    fix16Exc ret;
    ret.val = fix16_sin(x.val);
    return ret;
}

fix16Exc cos(fix16Exc x){
    fix16Exc ret;
    ret.val = fix16_cos(x.val);
    return ret;
}
