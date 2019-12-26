#ifndef dynamic_variable
#define dynamic_variable
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include"Int.h"
#include <iomanip>
enum typeName{is_none, is_bool, is_Int, is_float, is_string, is_varname, is_flow};
enum flowName{is_break, is_return, is_continue};
class dvar
{
    friend dvar operator+ (const dvar &I1, const dvar &I2);
    friend dvar operator* (const dvar &I1, const dvar &I2);
    friend dvar operator- (const dvar &I1, const dvar &I2);
    friend dvar operator/ (const dvar &I1, const dvar &I2);
    friend dvar operator% (const dvar &I1, const dvar &I2);
    friend dvar operator> (const dvar &I1, const dvar &I2);
    friend dvar operator>= (const dvar &I1, const dvar &I2);
    friend dvar operator<= (const dvar &I1, const dvar &I2);
    friend dvar operator< (const dvar &I1, const dvar &I2);
    friend dvar operator== (const dvar &I1, const dvar &I2);
    friend dvar operator!= (const dvar &I1, const dvar &I2);
    friend std::ostream& operator<< (std::ostream &os,const dvar &tmp);

    private:
    
    bool bvar;
    Int ivar;
    double fvar;
    std::string svar;
    typeName type;
    flowName flow;
    int flag;
    
    public:
    dvar()
    {
        type = is_string;
        flag = 1;
        svar = "";
        bvar = false;
    }
    dvar& operator= (const dvar & tmp)
    {
        bvar = tmp.getbool();
        ivar = Int(tmp.getInt());
        fvar = tmp.getfloat();
        svar = tmp.getstring();
        type = tmp.gettype();
        flag = tmp.getflag();
        flow = tmp.getflow();
        return *this;
    }
    dvar (const dvar &tmp)
    {
        bvar = tmp.getbool();
        ivar = Int(tmp.getInt());
        fvar = tmp.getfloat();
        svar = tmp.getstring();
        type = tmp.gettype();
        flag = tmp.getflag();
        flow = tmp.getflow();
    }
	explicit dvar(std::string const &s)
    {
        svar = s;
        flag = 1;
        switch(s[0])
        {
            case '\"' :
            { 
                type = is_string; 
                svar = s.substr(1, s.length() - 2);
                break;
            }

            case 'T' :
            {
                type = is_bool;
                bvar = true;
                break;
            }
            case 'F' :
            {
                type = is_bool;
                bvar = false;
                break;
            }
            case 'N' :
            {
                type = is_none;
                break;
            }
            default :
            {
                if (s[0] == '-') 
                {
                    flag = -1;
                    svar = s.substr(1, s.length() - 1);
                }
                else flag = 1;

                int i = 0;
                for(; i < svar.length(); ++i) 
                    if (svar[i] == '.') break;

                if(i <= svar.length() - 1) 
                {
                    type = is_float; 
                    fvar = atof(svar.c_str());
                } // convert to char* then to double
                    else
                        {
                            type = is_Int;
                            ivar = Int(svar,flag); 
                        }
            }
        }

    }

    explicit dvar(const Int &tmp)
    {
        ivar = tmp;
        flag = tmp.flag;
        svar = tmp.p;
        type = is_Int;
        
    }
     explicit dvar(const bool &tmp)
    {
        bvar = tmp;
        svar = (tmp) ? "True":"False";
        flag = 1;
        type = is_bool;
    }
    explicit dvar(const double &tmp) 
    {
        fvar = tmp;
        flag= 1;
        type = is_float;
        if(tmp < 0)
        {
            fvar = -fvar;
            flag = -1;
        }
        svar = std::to_string(fvar);
    
    } 

    void inivar(const std::string &tmp)
    {
        type = is_varname;
        svar = tmp;
        
    }

explicit operator bool() const
{
	bool tmp;
	switch(type)
    {
        case is_Int:
        {
            Int zero("0",1);
            tmp = (ivar != zero) ? true : false;
            break;
        }
        case is_float:
        {
            tmp = (bool) fvar;
            break;
        }
        case is_string:
        {
            tmp = (svar.length()) ? true: false;
            break;
        }
        case is_bool:
        {
            tmp = bvar;
            break;
        }
        case is_none:
        {
            tmp = false;
            break;
        }
    }
	return tmp;
}

explicit operator Int() const
{
	Int tmp;
    std::string tmpstr;
	switch(type)
    {
        case is_Int:
        {
            tmp = ivar;
            break;
        }
        case is_float:
        {
            int i = 0;
            for(; i < svar.length(); ++i)
                if (svar[i] == '.') break;
            if (i <= svar.length() - 1)
                tmpstr = svar.substr(i + 1, svar.length() - (i + 1));
            else tmpstr = svar;
            tmp = Int(tmpstr,flag);
            break;
        }
        case is_string:
        {
            tmp = Int(svar);
            break;
        }
        case is_bool:
        {
            tmp = (bvar == true) ? Int("1") : Int("0");
            break;
        }
        case is_none:
        {
            tmp = Int("0");
            break;
        }
    }
	return tmp;
}

explicit operator double() const
{
	double tmp;
	switch(type)
    {
        case is_Int:
        {
            tmp = double(ivar);
            break;
        }
        case is_float:
        {
            tmp = fvar;
            break;
        }
        case is_string:
        {
            tmp = double(Int(svar));
            break;
        }
        case is_bool:
        {
            tmp = (bvar) ? 1.0:0.0;
            break;
        }
        case is_none:
        {
            tmp = 0;
            break;
        }
    }
	return tmp;
}

explicit operator std::string() const 
{
   return svar;
}

dvar to_bool() 
{
    *this = dvar(bool(*this));
    return (*this);
}

dvar to_Int() 
{
    *this = dvar(Int(*this));
   return (*this);
}

dvar to_double() 
{
    *this = dvar(double(*this));
    return (*this);
}

dvar to_string() 
{
    *this = dvar(std::string(*this));
    return (*this);
}

std::string getstring() const
{
    return svar;
}
bool getbool() const
{
    return bvar;
}
double getfloat() const
{
    return fvar * flag;
}
Int getInt() const
{
    return ivar;
}
typeName gettype() const
{
    return type;
}
flowName getflow()const
{
    return flow;
}
int getflag() const
{
    return flag;
}


dvar &operator+= (const dvar & tmp)
{
    *this = (*this) + tmp;
    return (*this);
}
dvar &operator-= (const dvar & tmp)
{
    *this = (*this) - tmp;
    return (*this);
}
dvar &operator*= (const dvar & tmp)
{
    *this = (*this) * tmp;
    return (*this);
}
dvar &operator/= (const dvar & tmp)
{
    *this = (*this) / tmp;
    return (*this);
}
dvar &operator%= (const dvar & tmp)
{
    *this = (*this) % tmp;
    return (*this);
}
    
};

dvar operator+ (const dvar &I1, const dvar &I2) //暂时不考虑两个bool相加
{
    int max_convert = std::max(I1.gettype(), I2.gettype());
    dvar tmp;
    std::string zero = "\"";
    if(max_convert == is_string) 
    {
        tmp = dvar(zero + I1.getstring() + I2.getstring() + zero);
        return tmp;
    }
    if(max_convert == is_float)
    {
        tmp = dvar((double)I1 + (double)I2);
        return tmp;
    }
    if(max_convert == is_Int)
    {
        tmp = dvar((Int)I1 + (Int)I2);
        
        return tmp;
    }
    return tmp;
}
dvar operator- (const dvar &I1, const dvar &I2) 
{
    int max_convert = std::max(I1.gettype(), I2.gettype());
    dvar tmp;
    if(max_convert == is_float)
    {
        tmp = dvar((double)I1 - (double)I2);
        return tmp;
    }
    if(max_convert == is_Int)
    {
        tmp = dvar((Int)I1 - (Int)I2);
        return tmp;
    }
    return tmp;
}

dvar operator* (const dvar &I1, const dvar &I2) 
{
    int max_convert = std::max(I1.gettype(), I2.gettype());
    dvar tmp;
    std::string zero = "\"";
    if(max_convert == is_float)
    {
        tmp = dvar((double)I1 * (double)I2);
        return tmp;
    }
    if(max_convert == is_Int)
    {
        tmp = dvar((Int)I1 * (Int)I2);
        return tmp;
    }
    if(max_convert == is_string)
    {
        std::string ans = "";
        if(I1.gettype() == is_string)
        for(Int i = Int("1"); i <= I2.getInt(); i += Int("1"))
        ans = ans + I1.getstring();

        else
        for(Int i = Int("1"); i <= I1.getInt(); i += Int("1"))
        ans = ans + I2.getstring();

        return dvar(ans);
    }
    return tmp;
}

dvar operator/ (const dvar &I1, const dvar &I2) 
{
    int max_convert = std::max(I1.gettype(), I2.gettype());
    dvar tmp;
    if(max_convert == is_float)
    {
        tmp = dvar((double)I1 / (double)I2);
        return tmp;
    }
    if(max_convert == is_Int)
    {
        tmp = dvar((Int)I1 / (Int)I2);
        return tmp;
    }
    return tmp;
}

dvar operator% (const dvar &I1, const dvar &I2) 
{
    return dvar((Int)I1 % (Int)I2);
}

dvar operator> (const dvar &I1, const dvar &I2)
{
    int max_convert = std::max(I1.gettype(), I2.gettype());
    dvar tmp;
    if(max_convert == is_string) 
    {
        tmp = dvar(I1.getstring() > I2.getstring());
        return tmp;
    }
    if(max_convert == is_float)
    {
        tmp = dvar((double)I1 > (double)I2);
        return tmp;
    }
    if(max_convert == is_Int)
    {
        tmp = dvar((Int)I1 > (Int)I2);
        return tmp;
    }
    return tmp;
}
dvar operator== (const dvar &I1, const dvar &I2)
{
    int max_convert = std::max(I1.gettype(), I2.gettype());
    dvar tmp;
    if(max_convert == is_string) 
    {
        tmp = dvar(I1.getstring() == I2.getstring());
        return tmp;
    }
    if(max_convert == is_float)
    {
        tmp = dvar((double)I1 - (double)I2 < 1e-5);
        return tmp;
    }
    if(max_convert == is_Int)
    {
        tmp = dvar((Int)I1 == (Int)I2);
        return tmp;
    }
    return tmp;
}
dvar operator< (const dvar &I1, const dvar &I2)
{
    return dvar(!((I1 > I2).getbool()) && !((I1 == I2).getbool()));
}
 dvar operator>= (const dvar &I1, const dvar &I2)
{
    return dvar(!((I1 < I2).getbool()));
}
dvar operator<= (const dvar &I1, const dvar &I2)
{
    return dvar(!((I1 > I2).getbool()));
}
dvar operator!= (const dvar &I1, const dvar &I2)
{
    bool tmp;
    return dvar(!((I1 == I2).getbool()));
}
std::ostream& operator<< (std::ostream &os,const dvar &tmp)
{
    switch(tmp.gettype())
    {
        case is_Int:
        
        os << tmp.getInt();
        break;
        case is_float:
        printf("%.6f",tmp.getfloat());
        break;
        case is_bool:
        os << tmp.getstring();
        break;
        case is_string:
        os << tmp.getstring();
        break;
        case is_none:
        os << "None";
        break;
    }
    return os;
 
}

#endif