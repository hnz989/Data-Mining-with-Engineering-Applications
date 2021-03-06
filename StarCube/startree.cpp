#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include "logger.h"
#include "startable.h"
#include "startree.h"

using namespace std;


int index_array[] = {0,1,2,3};


// TreeNode* StarTree:: insert_single_val(string val , TreeNode* root){
//
// 	if(root){
// 		while(root  && root->val.compare(val]) != 0){
//
// 		}
// 		if(root)
//
// 	}else{
// 		cout <<  "Root null"<<endl;
// 	}
//
// }

TreeNode* StarTree:: insert(int row_idx , vector<string> row , TreeNode* root){




	if(row_idx  < row.size() - 1){ // dont insert count value from compressed table

		if(root){
			//cout << "index :" <<  row_idx << endl;
			//cout << "Insert into: " << root->val << " , "<< row_idx << " : " <<  row.size() << ", "<< row[row_idx] << endl;
			if(root->val.compare(row[index_array[row_idx]]) != 0){
				root->sibling = insert(row_idx, row, root->sibling);

			}else{
				root->count = root->count + stoi(row[4]) ;
				insert(row_idx+1 ,  row, root->child);

			}
			return root;


		}else{
			//cout << "Insert new node"<< " , "<< row_idx << " : " <<  row.size() << ", "<< row[row_idx] << endl;
			//create first child
			//cout << "index :" <<  row_idx << endl;
			TreeNode* node = new TreeNode();
			node->val = row[index_array[row_idx]];
			node->count = stoi(row[4]);
			node->child = insert(row_idx+1, row, node->child);
			return node;
		}
	}else{
		return NULL;
	}



}



/*
 * generate stare tree
 */
TreeNode* StarTree::generate_star_tree(vector<vector<string> > &table, TreeNode* root, int row_idx){

	//cout << "genarate star tree skip\n"<<endl;

	//for(int  i = 0 ; i <  skip.size();i++){
	//	cout << skip[i] << ", ";
	//}

	//cout <<endl;

	//int input;
	//cout <<"Enter to continue>>";
	//cin >> input;
	for(int i = 0 ; i <  table.size() ;i++){
		root->count = root->count + stoi(table[i][4]);
		root->child = insert(row_idx , table[i] ,  root->child);


	}
	this->root = root;



	if(DEBUG){
		TreeNode *temp = root->child;
		TreeNode *temp1 ;
		TreeNode *temp2 ;
		TreeNode *temp3 ;

		temp = root->child;
		while(temp){
			cout <<  temp->val << ":"<< temp->count << ",  "  <<  endl;
			temp1 = temp->child;
			while(temp1){
					cout <<  "  "<<  temp1->val << ":"<< temp1->count << ",  " << endl ;
					temp2 = temp1->child;
					while(temp2){
						cout <<  "    "<<  temp2->val << ":"<< temp2->count << ",  " ;
						temp3 = temp2->child;
						while(temp3){
							cout <<  "  "<<  temp3->val << ":"<< temp3->count << ",  " << endl ;
							if(temp3->child == NULL){
								cout <<  "     null"<<  endl ;
							}else{
								cout <<  "     notnull"<<  endl ;
							}
							temp3 = temp3->sibling;

							cout <<endl;
						}

						temp2 = temp2->sibling;
						cout <<endl;
					}
					temp1 = temp1->sibling;
					cout <<endl;
				}

			temp = temp->sibling;
			cout <<endl;
	}
	}


	return root;
}













