#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include "csvreader.h"
#include "logger.h"
#include "startable.h"
#include "startree.h"
#include "starcube.h"

using namespace std;

int iceberg = 200;
int level = 0;


string cuboid_val[] = {"*", "*" , "*", "*","*"};


string attr_names[] = {"*", "A" , "B", "C","D"};



StarCube ::StarCube(vector<vector<string> > csv_data, int iceberg)
{
	this->csv_data = csv_data;
	this->iceberg = iceberg;
	cuboid_key.clear();
}

void StarCube :: print_keys()
{
	cout <<  "This is the function to key value\n";
	for(auto it = cuboid_key.begin(); it != cuboid_key.end();it++)
    {
		cout <<it->first <<  " : " << it->second<< endl;
	}
}

void StarCube :: print_cuboid(int num)
{
	string key = cuboid_val[0] + "," +  cuboid_val[1] + "," + cuboid_val[2] + "," + cuboid_val[3] + "," + cuboid_val[4];
	if(cuboid_key.find(key) == cuboid_key.end())
    {
		cuboid_key.insert(pair<string ,int>(key, num));
	}
	else if(cuboid_key.find(key) != cuboid_key.end() && cuboid_key[key] < num)
    {
		cuboid_key[key] = num;
	}
}

bool StarCube :: all_stars_childs(TreeNode* root)
{
	if(root)
    {
		vector<TreeNode* >  child_list = get_childs(root);
		int size = child_list.size();
		for(int i  = 0 ; i < size  ; i++)
		{
			if(child_list[i]->val.compare("*")!= 0)
			{
				return false;
			}
			all_stars_childs(child_list[i]);
		}

		return true;
	}
	return false;
}

TreeNode* StarCube :: insert(TreeNode * root, string val, int count)
{

	if(root)
    {

		if(root->val.compare(val) == 0)
        {
			cout << "Add : " <<  root-> val << ", " <<  root->count << "+" <<  count <<  endl;
			root->count = root->count + count;
			return root;
		}
		else
        {
			if(root->val.substr(1) == val.substr(1)){
				TreeNode * temp = root;
				while(temp->sibling != NULL)
				{
					temp = temp->sibling;
				}
				temp->sibling = new TreeNode();
				temp->sibling->val = val;
				temp->sibling->count = count;
				return root;
			}
			else
            {
				root->child = insert(root->child ,  val, count);
				return root;
			}
		}


	}
	else
    {
		root = new TreeNode();
		root->val = val;
		root->count = count;
		return root;
	}
}
void StarCube :: star_cubing1(StarTree startree, TreeNode *root, TreeNode* cnode, int level, string cuboid[], vector<TreeNode*> subtree)
{

	if(cnode)
    {
		TreeNode *new_root = NULL;
		StarTree new_startree;

		if(cnode->count >= this->iceberg)
        {
			if(cnode !=  startree.root)
			{
				cuboid_val[level] = cnode->val;
				print_cuboid(cnode->count);
			}

			if(isleaf(cnode))
            {
				cuboid_val[level] = cnode->val;
				print_cuboid(cnode->count);
			}
			else
            {
				new_root = new TreeNode();
				string base = " ";
				for(int i = 1 ; i <  5 ; i++)
				{
					if(i < level + 1 )
					{
					    base = base + cuboid_val[i];
					}
					else if(i > level + 1)
                    {
						base = base + cuboid[i];
					}

				}

				new_root->val = cnode->val;;
				new_root->count = cnode->count;
				//cout << "Cuboid base: " <<  base<<endl;
				startree.root = new_root;
				subtree.push_back(new_root);
			}
		}

		if(!isleaf(cnode))
        {
			cuboid_val[level] = cnode->val;
			star_cubing1(startree,  root, cnode->child, level + 1, cuboid, subtree);
			//cuboid_val[level] = "*";
			star_cubing1(startree,  root, cnode->child, level + 1, cuboid, subtree);
		}

		if(new_root)
        {
			cuboid_val[level] = "*";
			star_cubing1(new_startree,  new_root, new_root, level, cuboid, subtree);
			subtree.pop_back();
		}

		if(cnode->sibling)
        {
			cuboid_val[level] = cnode->sibling->val;
			star_cubing1(startree,  root, cnode->sibling, level, cuboid,subtree);
		}

		cuboid_val[level] = "*";

	}

}


void StarCube :: star_cubing(TreeNode *root, TreeNode* cnode, int level)
{

	if(cnode)
    {
        vector<TreeNode* >  child_list = get_childs(cnode);
        int size = child_list.size();
        for(int i  = 0 ; i < size  ; i++)
        {
            if(child_list[i]->count >= iceberg)
            {
                if(!isleaf(child_list[i]))
                {
                    if( child_list[i]->val.compare("*") != 0)
                    {
                        cuboid_val[level] = child_list[i]->val;
                        star_cubing(root, child_list[i] ,  level + 1);
                        cuboid_val[level] = "*";
                        star_cubing(root, child_list[i] ,  level + 1);
                    }
                    else
                    {
                        cuboid_val[level] = "*";
                        star_cubing(root, child_list[i] ,  level + 1);
                    }
                }
                else
                {
                    cuboid_val[level] = child_list[i]->val;
                    print_cuboid(cnode->count);
                }
            }


        }

		print_cuboid(cnode->count);

	}

}


void  StarCube ::  print_cuboid()
{
	for(auto it = cuboid_key.begin();it != cuboid_key.end() ; it++)
    {
		char * m = strdup(it->first.c_str());
    	char * n = strtok(m, ",");
		n = strtok(NULL, ",");
    	while(n != NULL)
    	{
			cout << " " <<setw(2) <<  n;
        	n = strtok(NULL, ",");
    	}

		cout <<   " : " <<  it->second << endl;
		free(n);
		free(m);
	}
}

vector<TreeNode* > StarCube :: get_childs(TreeNode *root)
{
	vector<TreeNode* > child_list;
	if(root)
    {
		TreeNode * child;
		child = root->child;
		while(child)
		{
			child_list.push_back(child);
			child = child->sibling;
		}

	}
	return child_list;
}


bool StarCube :: isleaf(TreeNode* root)
{
	return root->child == NULL;
}














