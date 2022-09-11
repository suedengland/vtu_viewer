QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += /usr/include/vtk
DEPENDPATH += /usr/include/vtk
LIBS += -L/usr/lib/

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Based on https://github.com/drhalftone/QMake-PCL-VTK/blob/master/LAUPclVtkWidget.pro
LIBS += -lvtkChartsCore \
        -lvtkCommonColor \
        -lvtkCommonComputationalGeometry \
        -lvtkCommonCore \
        -lvtkCommonDataModel \
        -lvtkCommonExecutionModel \
        -lvtkCommonMath \
        -lvtkCommonMisc \
        -lvtkCommonSystem \
        -lvtkCommonTransforms \
        -lvtkDICOMParser \
        -lvtkDomainsChemistry \
        -lvtkDomainsChemistryOpenGL2 \
        -lvtkFiltersAMR \
        -lvtkFiltersCore \
        -lvtkFiltersExtraction \
        -lvtkFiltersFlowPaths \
        -lvtkFiltersGeneral \
        -lvtkFiltersGeneric \
        -lvtkFiltersGeometry \
        -lvtkFiltersHybrid \
        -lvtkFiltersHyperTree \
        -lvtkFiltersImaging \
        -lvtkFiltersModeling \
        -lvtkFiltersParallel \
        -lvtkFiltersParallelImaging \
        -lvtkFiltersPoints \
        -lvtkFiltersProgrammable \
        -lvtkFiltersSMP \
        -lvtkFiltersSelection \
        -lvtkFiltersSources \
        -lvtkFiltersStatistics \
        -lvtkFiltersTexture \
        -lvtkFiltersTopology \
        -lvtkFiltersVerdict \
        -lvtkGUISupportQt \
        -lvtkGUISupportQtSQL \
        -lvtkIOAMR \
        -lvtkIOCore \
        -lvtkIOEnSight \
        -lvtkIOExodus \
        -lvtkIOExport \
        -lvtkIOGeometry \
        -lvtkIOImage \
        -lvtkIOImport \
        -lvtkIOInfovis \
        -lvtkIOLSDyna \
        -lvtkIOLegacy \
        -lvtkIOMINC \
        -lvtkIOMovie \
        -lvtkIONetCDF \
        -lvtkIOPLY \
        -lvtkIOParallel \
        -lvtkIOParallelXML \
        -lvtkIOSQL \
        -lvtkIOTecplotTable \
        -lvtkIOVideo \
        -lvtkIOXML \
        -lvtkIOXMLParser \
        -lvtkImagingColor \
        -lvtkImagingCore \
        -lvtkImagingFourier \
        -lvtkImagingGeneral \
        -lvtkImagingHybrid \
        -lvtkImagingMath \
        -lvtkImagingMorphological \
        -lvtkImagingSources \
        -lvtkImagingStatistics \
        -lvtkImagingStencil \
        -lvtkInfovisBoostGraphAlgorithms \
        -lvtkInfovisCore \
        -lvtkInfovisLayout \
        -lvtkInteractionImage \
        -lvtkInteractionStyle \
        -lvtkInteractionWidgets \
        -lvtkParallelCore \
        -lvtkRenderingAnnotation \
        -lvtkRenderingContext2D \
        -lvtkRenderingContextOpenGL2 \
        -lvtkRenderingCore \
        -lvtkRenderingFreeType \
        -lvtkRenderingFreeTypeFontConfig \
        -lvtkRenderingGL2PSOpenGL2 \
        -lvtkRenderingImage \
        -lvtkRenderingLOD \
        -lvtkRenderingLabel \
        -lvtkRenderingOpenGL2 \
        -lvtkRenderingQt \
        -lvtkRenderingVolume \
        -lvtkRenderingVolumeOpenGL2 \
        -lvtkViewsContext2D \
        -lvtkViewsCore \
        -lvtkViewsInfovis \
        -lvtkViewsQt \
        -lvtksys \
        -lvtkverdict \
