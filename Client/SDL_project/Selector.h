#pragma once
#include "CompositeNode.h"
class Selector : public CompositeNode
{
public:
	virtual bool run() override 
	{
		//For each child
		for (TreeNode* child : getChildren()) 
		{ 
			// If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
			if (child->run())  
				return true;
		}
		return false;  // All children failed so the entire run() operation fails.
	}
};

