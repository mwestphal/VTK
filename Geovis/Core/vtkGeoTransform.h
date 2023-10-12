// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-FileCopyrightText: Copyright 2008 Sandia Corporation
// SPDX-License-Identifier: LicenseRef-BSD-3-Clause-Sandia-USGov
/**
 * @class   vtkGeoTransform
 * @brief   A transformation between two geographic coordinate systems
 *
 * This class takes two geographic projections and transforms point
 * coordinates between them.
 */

#ifndef vtkGeoTransform_h
#define vtkGeoTransform_h

#include "vtkAbstractTransform.h"
#include "vtkGeovisCoreModule.h" // For export macro

VTK_ABI_NAMESPACE_BEGIN
class vtkGeoProjection;

class VTKGEOVISCORE_EXPORT vtkGeoTransform : public vtkAbstractTransform
{
public:
  static vtkGeoTransform* New();
  void PrintSelf(ostream& os, vtkIndent indent) override;
  vtkTypeMacro(vtkGeoTransform, vtkAbstractTransform);

  ///@{
  /**
   * The source geographic projection, which can be set using
   * an external vtkGeoProjection, or using a proj string, in which
   * case the projection is allocated internally.
   */
  void SetSourceProjection(vtkGeoProjection* source);
  void SetSourceProjection(const char* proj);
  vtkGetObjectMacro(SourceProjection, vtkGeoProjection);
  ///@}

  ///@{
  /**
   * If true, we transform (x, y, z) otherwise
   * we transform (x, y) and leave z unchanged. Default is false.
   * This is used when converting from/to cartesian (cart) coordinate,
   * but it could be used for other transforms as well.
   */
  vtkSetMacro(TransformZCoordinate, bool);
  vtkGetMacro(TransformZCoordinate, bool);
  ///@}

  ///@{
  /**
   * The target geographic projection, which can be set using
   * an external vtkGeoProjection, or using a proj string, in which
   * case the projection is allocated internally.
   */
  void SetDestinationProjection(vtkGeoProjection* dest);
  void SetDestinationProjection(const char* dest);
  vtkGetObjectMacro(DestinationProjection, vtkGeoProjection);
  ///@}

  /**
   * Transform many points at once.
   */
  void TransformPoints(vtkPoints* src, vtkPoints* dst) override;

  /**
   * Invert the transformation.
   */
  void Inverse() override;

  ///@{
  /**
   * This will calculate the transformation without calling Update.
   * Meant for use only within other VTK classes.
   */
  void InternalTransformPoint(const float in[3], float out[3]) override;
  void InternalTransformPoint(const double in[3], double out[3]) override;
  ///@}

  ///@{
  /**
   * Computes Universal Transverse Mercator (UTM) zone given the
   * longitude and latitude of the point.
   * It correctly computes the zones in the two exception areas.
   * It returns an integer between 1 and 60 for valid long lat, or 0 otherwise.
   *
   */
  static int ComputeUTMZone(double lon, double lat);
  static int ComputeUTMZone(double* lonlat) { return ComputeUTMZone(lonlat[0], lonlat[1]); }
  ///@}

  ///@{
  /**
   * This will transform a point and, at the same time, calculate a
   * 3x3 Jacobian matrix that provides the partial derivatives of the
   * transformation at that point.  This method does not call Update.
   * Meant for use only within other VTK classes.
   */
  void InternalTransformDerivative(
    const float in[3], float out[3], float derivative[3][3]) override;
  void InternalTransformDerivative(
    const double in[3], double out[3], double derivative[3][3]) override;
  ///@}

  /**
   * Make another transform of the same type.
   */
  vtkAbstractTransform* MakeTransform() override;

protected:
  vtkGeoTransform();
  ~vtkGeoTransform() override;

  void InternalTransformPoints(double* ptsInOut, vtkIdType numPts, int stride);
  vtkGeoProjection* SourceProjection;
  vtkGeoProjection* DestinationProjection;
  bool TransformZCoordinate;

private:
  vtkGeoTransform(const vtkGeoTransform&) = delete;
  void operator=(const vtkGeoTransform&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif // vtkGeoTransform_h
