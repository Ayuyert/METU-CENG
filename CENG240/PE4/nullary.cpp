#include "type.h"
#include "nullary.h"

namespace sym 
{
	double Const::get_value() const { return value_; }
        Const::operator double() const { return value_; }

        bool Const::is_con() const{ return true; }

        __expr_t* Const::eval(const var_map_t& var_map) const {
            return new Const(value_);
        }

        __expr_t* Const::diff(const std::string& v) const {
            return new Const(0.0);
        }

        std::ostream& Const::operator<<(std::ostream& out) const  {
            out << value_;
            return out;
        }

        bool Const::operator==(const __expr_t& other) const {
            if (const Const* ustar = dynamic_cast<const Const*>(&other)) {
                return value_ == ustar->value_;
            }
            return false;}
}

namespace sym 
{
	std::string Var::get_variable() const { return var_;}
	Var::operator std::string () const { return var_;}
	
	bool Var::is_var() const { return true; }

	__expr_t* Var::eval(const var_map_t& vars) const { 
	     auto iter = vars.find(var_);
	     if(iter == vars.end()) {return new Var(var_);}
	     else return new Const(iter->second);
	}

	__expr_t* Var::diff(const std::string& v) const { 
	   if( v == var_) return new Const(1.0);
	   else return new Const(0.0);
	    
	}
	
	std::ostream& Var::operator<< (std::ostream &out) const {
	    out << var_;
	    return out;
	}

	bool Var::operator==(const __expr_t& other) const { 
	    
	     if (const Var* raki = dynamic_cast<const Var*>(&other)) {
                return var_ == raki->var_;
            }
            return false;
	    
	}
}

