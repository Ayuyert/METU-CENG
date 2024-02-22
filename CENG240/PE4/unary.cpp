#include "nullary.h"
#include "unary.h"
#include "binary.h"
#include <math.h>

namespace sym 
{
	bool NegOp::is_neg() const { return true;}

	__expr_t* NegOp::eval(const var_map_t& vars) const {
	   
	   if (const Const* const_expr = dynamic_cast<const Const*>(this->operand)){
	       double neg_value = (const_expr->get_value())*-1;
            return new Const(neg_value);
	   }
	   
	   return new NegOp(operand->eval());
	    
	}

	__expr_t* NegOp::diff(const std::string& v) const {
	
	    return NegOp(operand->diff(v)).eval();
	}

	std::ostream& NegOp::operator<< (std::ostream &out) const {
	    
	  out << "-";
        if (!this->operand->is_nullary()) {
            out << "(";
            this->operand->operator<<(out);
            out << ")";
        }
        else this->operand->operator<<(out);
        return out;
	    
	}

	bool NegOp::operator==(const __expr_t& other_) const { 
	    
	    if (const NegOp* neg_expr = dynamic_cast<const NegOp*>(&other_)) {
            return *(this->operand) == *(neg_expr->operand);
        }
        return false;
	    
	}
}

namespace sym 
{
	bool ExpOp::is_exp() const { return true; }

	__expr_t* ExpOp::eval(const var_map_t& vars) const { 
	    
	    if (const Const* const_expr = dynamic_cast<const Const*>(this->operand->eval(vars))) {
            double exp_value = std::exp(const_expr->get_value());
            
            return new Const(exp_value);
        }
       else  return new ExpOp(operand->eval(vars));
	    
	}

	__expr_t* ExpOp::diff(const std::string& v) const {
	    
	    __expr_t* diff_operand = this->operand->diff(v);
        return MulOp(diff_operand, ExpOp(this->operand->eval()).eval()).eval();
	    
	}

	std::ostream& ExpOp::operator<< (std::ostream &out) const { 
	    if(operand->is_nullary()){
	    out << "e^";
        this->operand->operator<<(out);}
        
        else{
            out << "e^";
            out << "(";
            this->operand->operator<<(out);
            out << ")";
            
        }
        
        return out;
	    
	}

	bool ExpOp::operator==(const __expr_t& other_) const {
	    
	    if (const ExpOp* exp_expr = dynamic_cast<const ExpOp*>(&other_)) {
            return *(this->operand) == *(exp_expr->operand);
        }
        else return false;
	    
	}
}
