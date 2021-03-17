#!/usr/bin/env python
import vtk

# Control the resolution of the test
radius = 10.0
res = 4
debug = 0
outputPoints = 1

# Create pipeline. Use two sphere sources:
# a portion of one sphere imprints on the other.
#
target = vtk.vtkSphereSource()
target.SetRadius(radius)
target.SetCenter(0,0,0)
target.LatLongTessellationOn()
target.SetThetaResolution(4*res)
target.SetPhiResolution(4*res)
target.SetStartTheta(0)
target.SetEndTheta(90)

imprint = vtk.vtkSphereSource()
imprint.SetRadius(radius)
imprint.SetCenter(0,0,0)
imprint.LatLongTessellationOn()
imprint.SetThetaResolution(8*res)
imprint.SetPhiResolution(4*res)
imprint.SetStartTheta(12)
imprint.SetEndTheta(57)
imprint.SetStartPhi(60.0)
imprint.SetEndPhi(120.0)

# Produce an imprint
imp = vtk.vtkImprintFilter()
imp.SetTargetConnection(target.GetOutputPort())
imp.SetImprintConnection(imprint.GetOutputPort())
imp.SetTolerance(0.075)
if debug:
    imp.SetOutputTypeToImprintedCells()
if outputPoints:
    imp.SetDebugOutputTypeToInputPoints()
else:
    imp.SetDebugOutputTypeToOutputTriangulation()
imp.SetDebugCellId(6)
imp.Update()

w = vtk.vtkPolyDataWriter()
w.SetInputConnection(imp.GetOutputPort())
w.SetFileName("imp.vtk")
#w.Write()
#exit()



impMapper = vtk.vtkPolyDataMapper()
impMapper.SetInputConnection(imp.GetOutputPort())
#impMapper.SetColorModeToMapScalars()
impMapper.SetScalarRange(0,2)
impMapper.SetScalarModeToUseCellFieldData()
impMapper.SelectColorArray("ImprintedCells")

impActor = vtk.vtkActor()
impActor.SetMapper(impMapper)
#impActor.GetProperty().SetRepresentationToWireframe()
impActor.GetProperty().SetColor(1,0,0)

imprintMapper = vtk.vtkPolyDataMapper()
imprintMapper.SetInputConnection(imprint.GetOutputPort())

imprintActor = vtk.vtkActor()
imprintActor.SetMapper(imprintMapper)
#imprintActor.GetProperty().SetRepresentationToWireframe()
imprintActor.GetProperty().SetColor(1,1,1)

fedges = vtk.vtkFeatureEdges()
fedges.SetInputConnection(imp.GetOutputPort())
fedges.ExtractAllEdgeTypesOff()
fedges.NonManifoldEdgesOn()
fedges.BoundaryEdgesOn()

fedgesMapper = vtk.vtkPolyDataMapper()
fedgesMapper.SetInputConnection(fedges.GetOutputPort())

fedgesActor = vtk.vtkActor()
fedgesActor.SetMapper(fedgesMapper)
fedgesActor.GetProperty().SetRepresentationToWireframe()
fedgesActor.GetProperty().SetColor(0,1,0)

# Second output if needed
if outputPoints:
    out2Mapper = vtk.vtkPointGaussianMapper()
    out2Mapper.EmissiveOff()
    out2Mapper.SetScaleFactor(0.05)
else:
    out2Mapper = vtk.vtkPolyDataMapper()
out2Mapper.SetInputConnection(imp.GetOutputPort(1))

out2Actor = vtk.vtkActor()
out2Actor.SetMapper(out2Mapper)
out2Actor.GetProperty().SetColor(1,1,0)

# Create the RenderWindow, Renderer
#
ren1 = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer( ren1 )
renWin.SetSize(300,200)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren1.AddActor(impActor)
#ren1.AddActor(imprintActor)
#ren1.AddActor(fedgesActor)
#ren1.AddActor(out2Actor)

cam = ren1.GetActiveCamera()
cam.SetPosition(1,0.5,0)
cam.SetFocalPoint(0,0,0)
ren1.ResetCamera()

renWin.Render()
iren.Start()
