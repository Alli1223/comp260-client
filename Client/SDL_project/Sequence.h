#pragma once
#include "CompositeNode.h"
class Sequence : public CompositeNode
{
public:

	virtual bool run() override 
	{
		// For each child if one fails then return false
		for (TreeNode* child : getChildren()) 
		{  
			if (!child->run()) 
				return false;
		}
		return true;  // Only if all children suceeded, the entire run() operation succeeds.
	}
};

