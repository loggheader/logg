#include "core/union_find/partition_image.hpp"
#include "core/union_find/UnionFind2D.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <cassert>


using namespace std;
using namespace cv;


/////////////////////////////////////////////////////////////////////////////////////////
/*
			basic function(s) to segment a Bool2d array
*/
std::vector<PointSet> partition_bool2d(Bool2d &array, bool white, bool black, int num_ways , cv::Point offset)
{
	assert(num_ways == 0 || num_ways == 4 || num_ways == 8);
	assert(white == true || black == true);
	
	bool black_8way, white_8way;
	if(num_ways == 8){
		white_8way = black_8way = true;
	}
	else if(num_ways == 4){
		white_8way = black_8way = false;
	}
	else{
		white_8way = true;
		black_8way = false;
	}

	int num_row = array.size();
	int num_col = array[0].size(); // add check for broken Bool2d
	UnionFind2D unionfind2d(num_row,num_col);

	for(int i=0;i<num_row;i++){
		for(int j=0;j<num_col;j++){
			if( (white && array[i][j]) || (black && !array[i][j]) ){
				if((i != num_row - 1) && !(array[i+1][j] ^ array[i][j]) ) unionfind2d.unite(i,j,i+1,j);
				if((j != num_col - 1) && !(array[i][j+1] ^ array[i][j]) ) unionfind2d.unite(i,j,i,j+1);

				if( (white_8way && array[i][j]) || (black_8way && !array[i][j]) ){
					if((i != num_row - 1) && (j != num_col -1) && !(array[i+1][j+1]^array[i][j])) unionfind2d.unite(i,j,i+1,j+1);
				    if((i != 0) && (j != num_col -1) && !(array[i-1][j+1]^array[i][j]) ) unionfind2d.unite(i,j,i-1,j+1);
				}

			}
		}
	}

	vector<int> count_help(num_row * num_col, 0);
	for(int i = 0; i < num_row; i++){
		for(int j = 0; j < num_col; j++){
			if( (array[i][j] && white) || (black && !array[i][j])){
				int parent = unionfind2d.root(i,j);
				if(count_help[parent] == 0) count_help[parent]++;
			}
		}
	}

	int number_of_sets_found = -1;
	for(int i = 0; i < num_row * num_col; i++){
		number_of_sets_found += count_help[i];
		count_help[i] = number_of_sets_found;
	}
	number_of_sets_found++;
	vector<PointSet> retval(number_of_sets_found);


	for(int i = 0; i<num_row; i++){
		for(int j=0; j<num_col; j++){
			if( (array[i][j] && white) || (black && !array[i][j])){
				int parent = unionfind2d.root(i,j);
				retval[count_help[parent]].push_back(Point(j,i));
			}
		}
	}

	return retval;
}














/////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat label_connected_components(const cv::Mat &img, int &num_labels, int num_ways, bool white_or_black)
{

	Mat image, labels;
	assert(img.channels() == 1);
	assert(num_ways == 0 || num_ways == 4 || num_ways == 8);
	if(num_ways == 0) num_ways = (white_or_black == true)? 8 : 4;
	if(white_or_black == true) image = img;
	else {
		image = img.clone();
		threshold(image,image,128,255,THRESH_BINARY_INV);
	}
	num_labels = connectedComponents(image,labels,num_ways,CV_16U,CCL_DEFAULT /*| CC_STAT_AREA */);
	return labels;
}


/*
std::vector<PointSet> get_pointsets_from_labels(LabelMat &labels, int num_labels)
{
	;
}
*/




