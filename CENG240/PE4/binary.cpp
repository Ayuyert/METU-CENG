#include "binary.h"
#include "nullary.h"
#include <math.h>

namespace sym 
{
	bool AddOp::is_add() const { return true; }

	__expr_t* AddOp::eval(const var_map_t& vars) const { 
        __expr_t* evalsol = lhs_->eval(vars);
        __expr_t* evalsag = rhs_->eval(vars);
        if(dynamic_cast<Const*>(evalsol)!=NULL && dynamic_cast<const Const*>(evalsag)!=NULL ){
            double sonuc = (dynamic_cast<const Const*>(evalsol)->get_value())+(dynamic_cast<const Const*>(evalsag)->get_value());
            delete evalsol;
            delete evalsag;
            return new Const(sonuc);
        }
        else if(dynamic_cast<const Const*>(evalsag)!=NULL && dynamic_cast<const Const*>(evalsag)->get_value() == 0){
            delete evalsag;
            return evalsol;
        }
        else if(dynamic_cast<const Const*>(evalsol)!=NULL && dynamic_cast<const Const*>(evalsol)->get_value() == 0){
            delete evalsol;
            return evalsag;
        }
        
        delete evalsol;
        delete evalsag;
        
        return new AddOp(lhs_->eval(vars),rhs_->eval(vars));
	}

	__expr_t* AddOp::diff(const std::string& v) const {
	
		__expr_t* lhs_diff = lhs_->diff(v);
		__expr_t* rhs_diff = rhs_->diff(v);
		
	
		return AddOp(lhs_diff, rhs_diff).eval();
	}

	std::ostream& AddOp::operator<< (std::ostream &out) const {
	
	    if(lhs_->is_nullary() == false){
	        out << "(";
	        lhs_->operator<<(out);
	        out << ")";
	        out << " + ";
	    }
	    else {
	        lhs_->operator<<(out);
	        out << " + ";
	        
	    }
	    
	    if(rhs_->is_nullary()==false){
	    out << "(";
	    rhs_->operator<<(out);
	    out << ")";  
	        
	    }
	   else {
	        rhs_->operator<<(out);
	        
	       
	   }
	    
		
		return out;
	}

	bool AddOp::operator==(const __expr_t& other_) const {
	
		if (typeid(other_) == typeid(AddOp)) {
			const AddOp& other = dynamic_cast<const AddOp&>(other_);
			return (*lhs_ == *other.lhs_ && *rhs_ == *other.rhs_);
		}
		else return false;
	}
	
}

namespace sym 
{
	bool MulOp::is_mul() const {return true; }

	__expr_t* MulOp::eval(const var_map_t& vars) const {
	    
	    __expr_t* evalsol = this->lhs_->eval(vars);
        __expr_t* evalsag = this->rhs_->eval(vars);
        if((dynamic_cast<const Const*>(evalsol)!=NULL && dynamic_cast<const Const*>(evalsol)->get_value() == 0 )|| 
        (dynamic_cast<const Const*>(evalsag)!=NULL && dynamic_cast<const Const*>(evalsag)->get_value() == 0)) {
            delete evalsag;
            delete evalsol;
            return new Const(0);}
        if(dynamic_cast<Const*>(evalsol)!=NULL && dynamic_cast<const Const*>(evalsag)!=NULL){
            
            if(dynamic_cast<const Const*>(evalsag)->get_value() == 0 || dynamic_cast<const Const*>(evalsag)->get_value() == 0) {
                delete evalsol;
                delete evalsag;
                return new Const(0);}
            
            double sonuc = (dynamic_cast<const Const*>(evalsol)->get_value())*(dynamic_cast<const Const*>(evalsag)->get_value());
            delete evalsol;
            delete evalsag;
            return new Const(sonuc);
        }
        
        else if(dynamic_cast<const Const*>(evalsol)!=NULL && dynamic_cast<const Const*>(evalsol)->get_value() == 1){
            delete evalsol;
            return evalsag;
        }
        
        
        else if(dynamic_cast<const Const*>(evalsag)!=NULL && dynamic_cast<const Const*>(evalsag)->get_value() == 1){
            delete evalsag;
            return evalsol;
        }
        
        
        else return new MulOp(lhs_->eval(vars),rhs_->eval(vars));
	    
	}

	__expr_t* MulOp::diff(const std::string& v) const { 
	    __expr_t* soldif = lhs_->diff(v);
		__expr_t* sagdif = rhs_->diff(v);
		return AddOp (MulOp(soldif,rhs_->eval()).eval(),MulOp(lhs_->eval(), sagdif).eval()).eval();
	}

	std::ostream& MulOp::operator<< (std::ostream &out) const { 
	    
	
	if(lhs_->is_nullary() == false){
	        out << "(";
	        lhs_->operator<<(out);
	        out << ")";
	        out << " * ";
	    }
	    else {
	        lhs_->operator<<(out);
	        out << " * ";
	        
	    }
	    
	    if(rhs_->is_nullary()==false){
	    out << "(";
	    rhs_->operator<<(out);
	    out << ")";  
	        
	    }
	   else {
	        rhs_->operator<<(out);
	        
	   }

		return out;
	    
	}

	bool MulOp::operator==(const __expr_t& other_) const {
	    
	    if (typeid(other_) == typeid(MulOp)) {
			return (*lhs_ == *dynamic_cast<const MulOp&>(other_).lhs_ && *rhs_ == *dynamic_cast<const MulOp&>(other_).rhs_);
		}
		else return false;
	    
	    
	}
}

