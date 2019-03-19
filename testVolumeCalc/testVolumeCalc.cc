// Include Files
#include <cmath>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <iostream>
//#include "rt_nonfinite.h"
//#include "testVolumeCalc.h"
//#include "bsxfun.h"

std::vector< std::vector<int> > Unique(std::vector< std::vector<int> >);
void PrintVectorDouble(std::vector<double>);
void PrintVectorInt(std::vector<int>);

int main () 
{

    double R = 2.0;

    std::vector<double> d1 { 1., 2., 3. };
    std::vector<double> d2 { 4., 5., 6. };
    std::vector<double> d3 { 3., 2., 1. };
    std::vector<double> d4 { 21., 22., 23. };
    std::vector<double> d5 { 3.5, 2., 3. };
    //std::vector< std::vector<double> > D { d1 };
    //std::vector< std::vector<double> > D { d1, d2 };
    //std::vector< std::vector<double> > D { d1, d2, d1, d3 };
    std::vector< std::vector<double> > D { d1, d5 };

    double voxelSide = 2.0 * R / 3.0;
    double voxelDimensions[3];
    voxelDimensions[0] = voxelSide / 2.0;
    voxelDimensions[1] = voxelSide / 2.0;
    voxelDimensions[2] = voxelSide / 2.0;

//    for ( int k = 0; k<3; k++ ) {
//        std::cout << voxelDimensions[k] << std::endl;
//    }

    // Apply offset of voxelDimensions to input points - store in tpPosData
    // Also divide each component by the voxel side, then floor the value - this gives an
    // integer-based transfer point (tp) position
    std::vector< std::vector<int> > tpPosData;
    std::vector<int>                tpPos;
    for ( std::vector<double> pos : D )
    {
        //std::cout << "Current vector: " << std::endl;
        //PrintVectorDouble(pos);
        for ( int i = 0; i < 3; i++ ) {
            pos.at(i) += voxelDimensions[i];
            pos.at(i) /= voxelSide;
            tpPos.push_back( std::floor(pos.at(i)) );
        }

        tpPosData.push_back(tpPos);
        tpPos.clear();
    }

    //std::cout << "All tps: " << std::endl;
    //for ( std::vector<int> vox : tpPosData ) {
    //    PrintVectorInt(vox);
    //}

    tpPosData = Unique(tpPosData);

    //std::cout << "Vector of unique tp positions:" << std::endl;
    //for ( std::vector<int> unique : tpPosData ) 
    //{
    //    PrintVectorInt(unique);
    //}

    double numTPs = tpPosData.size();
    //std::cout << "Number of unique tp positions: " << numTPs << std::endl;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    // Expand TP positions out in 3D (like meshgrid in matlab but without unnecessary - as no
    // plotting is taking place - copies of each vector)
    std::vector<int> currentPos;
    double x, y, z;
    int k0, k1, k2;
    std::vector<int> meshX, meshY, meshZ;
    std::vector< std::vector<int> > currentMesh;
    std::vector< std::vector< std::vector<int> > > fullMesh;
    double padding = 1;
    for ( int j=0; j<numTPs; j++) 
    {
        currentPos = tpPosData.at(j);
        //std::cout << "Current tp position being meshed:" << std::endl;
        //PrintVectorInt(currentPos);
        x = currentPos.at(0);
        y = currentPos.at(1);
        z = currentPos.at(2);

        for ( k0 = -1*padding; k0 < padding+1; ++k0 ) 
        {
            meshX.push_back( x + k0 );
            meshY.push_back( y + k0 );
            meshZ.push_back( z + k0 );
            
        }

        currentMesh.push_back(meshX);
        currentMesh.push_back(meshY);
        currentMesh.push_back(meshZ);

        meshX.clear();
        meshY.clear();
        meshZ.clear();

        fullMesh.push_back(currentMesh);

        currentMesh.clear();

    }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    // Find all x,y,z combinations (positions voxels describing the associated volume about the
    // transfer points - although not centred)
    // Any overlapping voxels will later be removed to avoid double counting
    std::vector< std::vector<int> > collapsedMesh;
    std::vector<int>                voxelCoord;

    int voxelXCoord, voxelYCoord, voxelZCoord;
    for ( auto const mesh : fullMesh )
    {
        for ( int ix=0; ix<3; ++ix )
        {
            for ( int iy=0; iy<3; ++iy )
            {
                for ( int iz=0; iz<3; ++iz )
                {
                    voxelXCoord = mesh.at(0).at(ix);
                    voxelYCoord = mesh.at(1).at(iy);
                    voxelZCoord = mesh.at(2).at(iz);

                    voxelCoord.push_back(voxelXCoord);
                    voxelCoord.push_back(voxelYCoord);
                    voxelCoord.push_back(voxelZCoord);

                    collapsedMesh.push_back(voxelCoord);

                    voxelCoord.clear();
                }
            }

        }

    }

    //for ( auto row : collapsedMesh )
    //{
    //    PrintVectorInt(row);
    //    std::cout << std::endl;
    //}

    //std::cout << "Number of voxels (not necessarily unique): " << collapsedMesh.size() << std::endl;

    // Remove overlapping voxels
    collapsedMesh = Unique(collapsedMesh);
    //for ( auto uniqueRow : collapsedMesh )
    //{
    //    PrintVectorInt(uniqueRow);
    //    std::cout << std::endl;
    //}

    int nUnique = collapsedMesh.size();
    std::cout << "Number of unique voxel sections: " << nUnique << std::endl;

    // Calculate the approximate associated volume (aAV) - it is a relative, not absolute, value
    double aAV = nUnique * (M_PIl / 6.) * std::pow(voxelSide, 3);

    double worstCase = D.size() * M_PIl * std::pow(R,3) * 4./3.;

    std::cout << "aAV: " << aAV << " nm3" << '\n';
    std::cout << "worst case spheres: " << worstCase << " nm3" << '\n';


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    return 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector< std::vector<int> > Unique( std::vector< std::vector<int> > vec )
{
    std::vector< std::vector<int> >::const_iterator it0;
    std::vector< std::vector<int> >::iterator it1;
    // In a set, each value serves as its own key and must be unique.
    // When inserting into a set, there is a check to ensure that the element to be inserted does
    // not already exist in the set. If it does, the element will not be inserted but rather the
    // function will return an iterator to the equivalent element already in the set. This boolean
    // check can be accessed using (*insert iterator).second (true if unique, false if not inserted)
    std::set< std::vector<int> > uniquePos;
    bool isUniquePos;

    //std::cout << "Finding unique values. Checking: " << std::endl;
    for( it0 = vec.begin(), it1 = vec.begin(); it0 != vec.end(); ++it0 ) 
    {
        // If the element was the first with its value (and was thus inserted), set the current value
        // pointed to by it1 to this and then increment it1. This 'overwrites' the current value of
        // vec with only unique values. Once it0 reaches the end, the new vec written by it1 will be
        // shorter than the original by the number of elements between the current memory address
        // pointed to by it1 and the end of the originally allocated memory for vec. Therefore, the
        // original value will remain there (meaning at least one duplicate will exist). This is 
        // solved by an erase call after the loop.
        isUniquePos = uniquePos.insert(*it0).second;
        if( isUniquePos ) 
        {
            *it1++ = *it0;
        }

    }
    
    // Clear extraneous values at the end of tpPosData
    vec.erase( it1, vec.end() );

    return vec;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrintVectorDouble(std::vector<double> vec)
{
    for ( auto it = vec.begin(); it != vec.end(); ++it ) 
    {
        std::cout << *it << "    ";
    } 
    std::cout << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrintVectorInt(std::vector<int> vec)
{
    for ( auto it = vec.begin(); it != vec.end(); ++it ) 
    {
        std::cout << *it << "    ";
    }
    std::cout << std::endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Extra code
//

    //std::vector< std::vector<int> >::const_iterator it0;
    //std::vector< std::vector<int> >::iterator it1;
    //// In a set, each value serves as its own key and must be unique.
    //// When inserting into a set, there is a check to ensure that the element to be inserted does
    //// not already exist in the set. If it does, the element will not be inserted but rather the
    //// function will return an iterator to the equivalent element already in the set. This boolean
    //// check can be accessed using (*insert iterator).second (true if unique, false if not inserted)
    //std::set< std::vector<int> > uniquePos;
    //bool isUniquePos;

    ////std::cout << "Finding unique values. Checking: " << std::endl;
    //for( it0 = tpPosData.begin(), it1 = tpPosData.begin(); it0 != tpPosData.end(); ++it0 ) 
    //{
    //    //PrintVectorInt(*it0);

    //    //std::cout << "*it1:" << std::endl;
    //    //PrintVectorInt(*it1);
    //    //std::cout << "*it0:" << std::endl;
    //    //PrintVectorInt(*it0);

    //    // If the voxel was the first of its value (and was thus inserted), set the current value
    //    // pointed to by it1 to this and then increment it1. This 'overwrites' the current value of
    //    // tpPosData with only unique values. Once it0 reaches the end, the new tpPosData
    //    // written by it1 will be shorter than the original by the number of elements between the
    //    // current memory address pointed to by it1 and the end of the originally allocated memory
    //    // for tpPosData. Therefore, the original value will remain there (meaning at least one
    //    // duplicate will exist). This is solved by the erase call after the loop.
    //    isUniquePos = uniquePos.insert(*it0).second;
    //    //std::cout << "Unique? " << isUnique << std::endl;

    //    if( isUniquePos ) 
    //    {
    //        *it1++ = *it0;
    //        //PrintVectorInt(*it1);
    //    }

    //    //std::cout << "Current iteration: " << std::endl;
    //    //for ( auto uniP : uniquePos ) {
    //    //    PrintVectorInt(uniP);
    //    //}

    //}

    //std::cout << "'New' tpPosData before erase call:" << std::endl;
    //for ( auto voxOrder : tpPosData ) 
    //{
    //    PrintVectorInt(voxOrder);
    //}
    
    //// Clear extraneous values at the end of tpPosData
    //tpPosData.erase( it1, tpPosData.end() );


    //std::vector< std::vector<int> > currentMeshX, currentMeshY, currentMeshZ;
    //std::vector< std::vector< std::vector<int> > > meshX, meshY, meshZ;
    //std::vector< std::vector< std::vector< std::vector<int> > > > currentMesh;
    //std::vector< std::vector< std::vector< std::vector< std::vector<int> > > > > fullMesh;

        //for ( k1=0; k1<3; ++k1 )
        //{
        //    
        //    currentMeshX.push_back(partialMeshX);
        //    currentMeshY.push_back(partialMeshY);
        //    currentMeshZ.push_back(partialMeshZ);

        //}
        
        //partialMeshX.clear();
        //partialMeshY.clear();
        //partialMeshZ.clear();

        //for ( k2=0; k2<3; ++k2 )
        //{
        //    meshX.push_back(currentMeshX);
        //    meshY.push_back(currentMeshY);
        //    meshZ.push_back(currentMeshZ);
        //
        //}

//        std::cout << "Current x mesh:" << std::endl;
//        for ( auto x : currentMeshX )
//        {
//            PrintVectorInt(x);
//        }
//        std::cout << "Current y mesh:" << std::endl;
//        for ( auto y : currentMeshY )
//        {
//            PrintVectorInt(y);
//        }
//        std::cout << "Current z mesh:" << std::endl;
//        for ( auto z : currentMeshZ )
//        {
//            PrintVectorInt(z);
//        }

        //currentMeshX.clear();
        //currentMeshY.clear();
        //currentMeshZ.clear();

        //std::cout << "x Mesh:" << std::endl;
        //for ( auto xM : meshX )
        //{
        //    for ( auto x : xM )
        //    {
        //        PrintVectorInt(x);
        //    }
        //    std::cout << std::endl;
        //}

        //std::cout << "y Mesh:" << std::endl;
        //for ( auto yM : meshY )
        //{
        //    for ( auto y : yM )
        //    {
        //        PrintVectorInt(y);
        //    }
        //    std::cout << std::endl;
        //}

        //std::cout << "z Mesh:" << std::endl;
        //for ( auto zM : meshZ )
        //{
        //    for ( auto z : zM )
        //    {
        //        PrintVectorInt(z);
        //    }
        //    std::cout << std::endl;
        //}


        //currentMesh.push_back(meshX);
        //currentMesh.push_back(meshY);
        //currentMesh.push_back(meshZ);

        //meshX.clear();
        //meshY.clear();
        //meshZ.clear();
//        std::cout << "Current mesh:" << "\n" << std::endl;
//        for ( auto mesh : currentMesh )
//        {
//            for ( auto partialMesh : mesh )
//            {
//                for ( auto meshComp : partialMesh )
//                {
//                    PrintVectorInt(meshComp);
//                }
//                std::cout << std::endl;
//            }
//            std::cout << "----" << "\n" << std::endl;
//        }
//
//    std::cout << "Full mesh:" << "\n" << std::endl;
//    for ( auto mesh : fullMesh )
//    {
//
//        for ( auto coordMesh : mesh )
//        {
//            for ( auto partialMesh : coordMesh )
//            {
//                for ( auto meshComp : partialMesh )
//                {
//                    PrintVectorInt(meshComp);
//                }
//                std::cout << std::endl;
//            }
//            std::cout << "----" << "\n" << std::endl;
//        }
//        std::cout << "----" << "\n" << std::endl;
//    }

