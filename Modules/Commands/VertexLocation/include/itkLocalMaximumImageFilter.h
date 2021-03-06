/*=========================================================================


authors: Bryn A. Lloyd, Simon K. Warfield, Computational Radiology Laborotory (CRL), Brigham and Womans
  date: 06/30/2005
  
  Acknowledgements:
This investigation was supported in part by NSF ITR 0426558 and 
NIH grants R21 MH67054 and P41 RR13218.

=========================================================================*/
#ifndef __itkLocalMaximumImageFilter_h
#define __itkLocalMaximumImageFilter_h

#include "itkImageToMeshFilter.h"
#include "itkImage.h"

#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkMacro.h"
#include "tttDescriptionDataTypes.h"
#include <vector>

namespace itk
{
/** \class LocalMaximumImageFilter
 * \brief Calculates the Local Maximum values and puts them in a point-set/ mesh.
 *
 * This filter finds the local maxima of an image. The result is returned as a PointSet. 
 * Additionally a binary image, with 0 for background, and 1 for the points can be retrieved. 
 * 
 * This filter assumes a pixel must be larger or equal all of it's neighbors to be a maximum.
 * The neighborhood size can be set by setting the Radius. The second parameter is a threshold.
 * Only maxima above the threshold are selected.
 *
 * TODO: allow user to set which information should be saved in the point-set (i.e. index or physical point, data)
 *
 *
 * \sa Image
 * \sa Neighborhood
 * \sa NeighborhoodOperator
 * \sa NeighborhoodIterator
 *
 * \ingroup IntensityImageFilters
 */
template <class TInputImage>
class ITK_EXPORT LocalMaximumImageFilter : public itk::ProcessObject
{
public:


  /** Run-time type information (and related methods). */
  itkTypeMacro(LocalMaximumImageFilter, ImageToMeshFilter);


  /** Extract dimension from input and output image. */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Some typedefs associated with the input images. */
  typedef TInputImage                               InputImageType;
  typedef typename InputImageType::Pointer          InputImagePointer;
  typedef typename InputImageType::ConstPointer     InputImageConstPointer;
  typedef typename InputImageType::RegionType       InputImageRegionType;
  typedef ImageRegionConstIteratorWithIndex<InputImageType> InputImageIterator;


  typedef typename ttt::AdherensJunctionVertices<InputImageDimension> LocalMaximaContainerType;

  typedef typename LocalMaximaContainerType::Pointer LocalMaximaContainerPointerType;

  /** Image typedef support. */
  typedef typename InputImageType::PixelType InputPixelType;



  typedef typename InputImageType::SizeType InputSizeType;
  typedef typename InputImageType::IndexType InputIndexType;

  typedef ImageRegionIteratorWithIndex<InputImageType> OutputImageIterator;


  /** Standard class typedefs. */
  typedef LocalMaximumImageFilter Self;
  typedef itk::ProcessObject Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Set the radius of the neighborhood used to compute the mean. */
  itkSetMacro(Radius, InputSizeType);
  /** Get the radius of the neighborhood used to compute the mean */
  itkGetConstReferenceMacro(Radius, InputSizeType);

  /** Set the radius of the neighborhood used to compute the mean. */
  itkSetMacro(Threshold, InputPixelType);
  /** Get the radius of the neighborhood used to compute the mean */
  itkGetConstReferenceMacro(Threshold, InputPixelType);


  itkGetObjectMacro(Input,InputImageType);
  itkSetObjectMacro(Input,InputImageType);
  inline LocalMaximaContainerPointerType GetOutput(){
	  return m_LocalMaxima;
  }
  virtual void  GenerateData ();
protected:
  LocalMaximumImageFilter();
  virtual ~LocalMaximumImageFilter() {}
  void PrintSelf(std::ostream& os, Indent indent) const;


  /** LocalMaximumImageFilter can be implemented as a multithreaded filter.
   * Therefore, this implementation provides a ThreadedGenerateData()
   * routine which is called for each processing thread. The output
   * image data is allocated automatically by the superclass prior to
   * calling ThreadedGenerateData().  ThreadedGenerateData can only
   * write to the portion of the output image specified by the
   * parameter "outputRegionForThread"
   *
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData() */




private:
  LocalMaximumImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  InputSizeType m_Radius;
  InputPixelType m_Threshold;

  typename InputImageType::Pointer m_Input;

  LocalMaximaContainerPointerType m_LocalMaxima;
  //InputImagePointer m_BinaryImage;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkLocalMaximumImageFilter.txx"
#endif

#endif
