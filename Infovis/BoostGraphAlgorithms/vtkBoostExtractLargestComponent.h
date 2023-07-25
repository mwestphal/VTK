// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkBoostExtractLargestComponent
 * @brief   Extract the largest connected
 * component of a graph
 *
 *
 * vtkBoostExtractLargestComponent finds the largest connected region of a
 * vtkGraph. For directed graphs, this returns the largest biconnected component.
 * See vtkBoostConnectedComponents for details.
 */

#ifndef vtkBoostExtractLargestComponent_h
#define vtkBoostExtractLargestComponent_h

#include "vtkGraphAlgorithm.h"
#include "vtkInfovisBoostGraphAlgorithmsModule.h" // For export macro

VTK_ABI_NAMESPACE_BEGIN
class vtkGraph;

class VTKINFOVISBOOSTGRAPHALGORITHMS_EXPORT vtkBoostExtractLargestComponent
  : public vtkGraphAlgorithm
{
public:
  vtkTypeMacro(vtkBoostExtractLargestComponent, vtkGraphAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Construct an instance of vtkBoostExtractLargestComponent with
   * InvertSelection set to false.
   */
  static vtkBoostExtractLargestComponent* New();

  ///@{
  /**
   * Set the flag to determine if the selection should be inverted.
   */
  vtkSetMacro(InvertSelection, bool);
  vtkGetMacro(InvertSelection, bool);
  ///@}

protected:
  vtkBoostExtractLargestComponent();
  ~vtkBoostExtractLargestComponent() override = default;

  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  /**
   * Store the choice of whether or not to invert the selection.
   */
  bool InvertSelection;

private:
  vtkBoostExtractLargestComponent(const vtkBoostExtractLargestComponent&) = delete;
  void operator=(const vtkBoostExtractLargestComponent&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
