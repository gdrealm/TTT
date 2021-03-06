/*
 * EdgeSelectionInteractor.cpp
 *
 *  Created on: 04/02/2014
 *      Author: rod
 */

#include "EdgeSelectionInteractor.h"

#include <vtkPropPicker.h>
#include <vtkRenderWindowInteractor.h>
void EdgeSelectionInteractor::OnLeftButtonDown(){
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	int* clickPos = this->GetInteractor()->GetEventPosition();

	// Pick from this location.
	vtkSmartPointer<vtkPropPicker>  picker =  	vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick(clickPos[0], clickPos[1], 0, m_Renderer);

	vtkSmartPointer<vtkActor> pickedActor = picker->GetActor();

	if(pickedActor){
		this->SetSelection(pickedActor);
	}


}
void EdgeSelectionInteractor::OnRightButtonUp(){
	vtkInteractorStyleTrackballCamera::OnRightButtonUp();
	this->UnsetSelection();

}

EdgeSelectionInteractor::EdgeSelectionInteractor() {

	m_PickedEdgeActor=0;
	m_PickedProperty=vtkSmartPointer<vtkProperty>::New();
}

