#ifndef __itkEmptynessMeasurementFunction_h
#define __itkEmptynessMeasurementFunction_h

#include "tttObjectnessMeasurementFunction.h"

namespace ttt {

/**
 * TODO
 */
class EmptynessMeasurementFunction: public ObjectnessMeasurementFunction {
public:

	/**
	 * TODO
	 */
	typedef EmptynessMeasurementFunction Self;
	/**
	 * TODO
	 */
	typedef LightObject Superclass;
	/**
	 * TODO
	 */
	typedef SmartPointer<Self> Pointer;
	/**
	 * TODO
	 */
	typedef SmartPointer<const Self> ConstPointer;

	/** Run-time type information (and related methods) */
	itkTypeMacro(EmptynessMeasurementFunction, ObjectnessMeasurementFunction)
	;

	/**
	 * TODO
	 */
	itkNewMacro(Self)
	;

	/**
	 * TODO
	 */
	inline void SetAlpha(double alpha) {
		m_Alpha = alpha;
	}

	/**
	 * TODO
	 */
	itkGetMacro(Alpha, double)
	;

	/** Set/Get macros for Beta */
	inline void SetBeta(double beta) {
		m_Beta = beta;
	}

	/**
	 * TODO
	 */
	itkGetMacro(Beta, double)
	;

	/** Set/Get macros for Gamma */
	inline void SetGamma(double gamma) {
		m_Gamma = gamma;
	}
	/**
	 * TODO
	 */
	itkGetMacro(Gamma, double)
	;

	/** Set/Get macros for C */
	inline void SetC(double C) {
		m_C = C;
	}
	/**
	 * TODO
	 */
	itkGetMacro(C, double)
	;

	/** Macro to scale the vesselness measure with the
	 largest eigenvalue or not */
	inline void SetScaleVertexnessMeasure(bool scale) {
		m_ScaleVertexnessMeasure = scale;
	}
	/**
	 * TODO
	 */
	itkGetMacro( ScaleVertexnessMeasure, bool )
	;
	/**
	 * TODO
	 */
	itkBooleanMacro(ScaleVertexnessMeasure)
	;

	/**
	 * TODO
	 * @param eigenValue
	 * @return
	 */
	virtual double ComputeObjectProperty(
			const FixedArray<double, 3> & eigenValue) {
		//

		double result = 0;
		// Find the smallest eigenvalue
		double smallest = vnl_math_abs(eigenValue[0]);
		double Lambda1 = eigenValue[0];
		for (unsigned int i = 1; i <= 2; i++) {
			if (vnl_math_abs(eigenValue[i]) < smallest) {
				Lambda1 = eigenValue[i];
				smallest = vnl_math_abs(eigenValue[i]);
			}
		}

		// Find the largest eigenvalue
		double largest = vnl_math_abs(eigenValue[0]);
		double Lambda3 = eigenValue[0];

		for (unsigned int i = 1; i <= 2; i++) {
			if (vnl_math_abs(eigenValue[i] > largest)) {
				Lambda3 = eigenValue[i];
				largest = vnl_math_abs(eigenValue[i]);
			}
		}

		//  find Lambda2 so that |Lambda1| < |Lambda2| < |Lambda3|
		double Lambda2 = eigenValue[0];

		for (unsigned int i = 0; i <= 2; i++) {
			if (eigenValue[i] != Lambda1 && eigenValue[i] != Lambda3) {
				Lambda2 = eigenValue[i];
				break;
			}
		}

		assert(vnl_math_abs(Lambda3) > vnl_math_abs(Lambda2));
		assert(vnl_math_abs(Lambda2) > vnl_math_abs(Lambda1));

		if(Lambda3<0 || Lambda2 < 0 || Lambda1 < 0){
			return 0;
		}
		double S = vcl_sqrt(Lambda1 * Lambda1 + Lambda2 * Lambda2 * Lambda3 * Lambda3);

		double Lambda3Sqr = vnl_math_sqr(Lambda3);

		double GammaSqr = m_Gamma * m_Gamma;
		double AlphaSqr = m_Alpha * m_Alpha;
		double BetaSqr = m_Beta * m_Beta;
		double term1 = (vcl_exp(-1.0 * ((vnl_math_sqr(S))) / (2.0 * GammaSqr)));
		//double term4 = vcl_exp(-1.0 * (2.0 * vnl_math_sqr(m_C)) / (Lambda3Sqr));
			//			double term1 =  ( 1 - vcl_exp( -1.0 * (S)));
			//			double term2  = ( 1 - vcl_exp( -1.0 * (A)));
			//			double term3  = ( 1 - vcl_exp( -1.0 * (B)));

		double vertexnessMeasure = term1 ;

		if (m_ScaleVertexnessMeasure) {
			double Lambda3Abs = vcl_abs(Lambda3);
			result = Lambda3Abs * vertexnessMeasure;
		} else {
			result = vertexnessMeasure;
		}
		return (result);
	}

protected:
	/**
	 * TODO
	 */
	EmptynessMeasurementFunction() {
		m_Alpha = 0.5;
		m_Beta = 0.5;
		m_Gamma = 8;
		m_C = 10e-6;
		m_ScaleVertexnessMeasure = false;
	}
	/**
	 * TODO
	 */
	virtual ~EmptynessMeasurementFunction() {

	}
	/**
	 * TODO
	 * @param os
	 * @param indent
	 */
	void PrintSelf(std::ostream & os, Indent indent) const {

		os << indent << "Alpha: " << m_Alpha << std::endl;
		os << indent << "Beta:  " << m_Beta << std::endl;
		os << indent << "Gamma: " << m_Gamma << std::endl;

		os << indent << "C: " << m_C << std::endl;
		;
	}

private:
	/**
	 * TODO
	 * @param
	 */
	EmptynessMeasurementFunction(const Self &); //purposely not implemented
	/**
	 * TODO
	 * @param
	 */
	void operator=(const Self &);           //purposely not implemented

	/**
	 * TODO
	 */
	double m_Alpha;
	/**
	 * TODO
	 */
	double m_Beta;
	/**
	 * TODO
	 */
	double m_Gamma;
	/**
	 * TODO
	 */
	double m_C;
	/**
	 * TODO
	 */
	bool m_ScaleVertexnessMeasure;

};
} // end namespace itk

#endif
