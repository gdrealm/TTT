//    This file is part of TTT Tissue Tracker.
//
//    TTT Tissue Tracker is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    TTT Tissue Tracker is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with TTT Tissue Tracker.  If not, see <http://www.gnu.org/licenses/>.

/** \addtogroup TTTTectonics
 *  @{
 */

#ifndef TECTONICSCOMMAND_H_
#define TECTONICSCOMMAND_H_

#include "AppCommand.h"
#include "tectonics.h"
#include "Ellipse.h"
#include "tttDescriptionDataTypes.h"
namespace ttt{
class TectonicsCommand: public AppCommand {

private:

	typedef Ellipse<double> EllipseType;
	typedef std::map<typename TrackedTissueDescriptor::DualGraphVertexDescriptorType,EllipseType >   EllipseMapType;
	typedef boost::shared_ptr<EllipseMapType > EllipseMapTypePointer;



	TrackedTissueDescriptor::Pointer m_PreviousDescriptor;
	TrackedTissueDescriptor::Pointer m_CurrentDescriptor;
	TrackedTissueDescriptor::Pointer m_NextDescriptor;

	boost::shared_ptr<std::vector<TrackedDomain> > m_Domains;

	EllipseMapTypePointer  m_PreviousEllipses;
	EllipseMapTypePointer  m_CurrentEllipses;
	EllipseMapTypePointer  m_NextEllipses;

	DomainStrainRatesMapTypePointer m_DomainStrainRates;

public:
	TectonicsCommand();

	inline void SetDomains(const boost::shared_ptr<std::vector<TrackedDomain> > & domains){
		m_Domains=domains;
	}
	inline void SetEllipsesPrevious(const EllipseMapTypePointer & ellipses){
		m_PreviousEllipses=ellipses;

	}
	inline void SetEllipsesNext(const EllipseMapTypePointer & ellipses){
		m_NextEllipses=ellipses;
	}
	inline void SetEllipsesCurrent(const EllipseMapTypePointer & ellipses){
		m_CurrentEllipses=ellipses;
	}
	inline void SetCurrentTrackedTissueDescriptor(const TrackedTissueDescriptor::Pointer descriptor){
		m_CurrentDescriptor=descriptor;
	}
	inline void SetPreviousTrackedTissueDescriptor(const TrackedTissueDescriptor::Pointer descriptor){
		m_PreviousDescriptor=descriptor;
	}
	inline void SetNextTrackedTissueDescriptor(const TrackedTissueDescriptor::Pointer descriptor){
		m_NextDescriptor=descriptor;
	}
	inline DomainStrainRatesMapTypePointer GetDomainStrainRates(){
		return m_DomainStrainRates;
	}
	virtual ~TectonicsCommand();
	virtual void Do();
};
}
#endif /* TECTONICSCOMMAND_H_ */
/** @}*/
