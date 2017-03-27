#pragma once
#include "stdafx.h"

// This is the root class for each node
// These classes and code are copied and modified from this CPP fourm code http://www.cplusplus.com/forum/general/141582/

class BehaviourTree
{

public:
	std::string leafNodeToRun = "NA";
	class Node
	{
	public:

		virtual bool run() = 0;
	};

	class Root : public Node {
	private:
		Node* child;
		friend class BehaviourTree;
		void setChild(Node* newChild) { child = newChild; }
		virtual bool run() override { return child->run(); }
	};

	class CompositeNode : public Node
	{  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
	private:
		std::vector<Node*> children;
	public:
		const std::vector<Node*>& getChildren() const {return children;}
				void addChild (Node* child) {children.emplace_back(child);}
				void addChildren (std::initializer_list<Node*>&& newChildren) {for (Node* child : newChildren) addChild(child);}
				template <typename CONTAINER>
				void addChildren (const CONTAINER& newChildren) {for (Node* child : newChildren) addChild(child);}
			protected:
				std::vector<Node*> childrenShuffled() const {std::vector<Node*> temp = children;  std::random_shuffle (temp.begin(), temp.end());  return temp;}
	};

	// If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
	class Selector : public CompositeNode
	{
	public:
		virtual bool run() override
		{
			for (Node* child : getChildren())
			{  // The generic Selector implementation
				if (child->run())  
					return true;
			}
			return false;  // All children failed so the entire run() operation fails.
		}
	};

	// If one child fails, then enter operation run() fails.  Success only results if all children succeed.
	class Sequence : public CompositeNode
	{
	public:
		virtual bool run() override
		{
			for (Node* child : getChildren())
			{  // The generic Sequence implementation.
				if (!child->run())  
					return false;
			}
			return true;  // All children suceeded, so the entire run() operation succeeds.
		}
	};
private:
	Root* root;
public:
	BehaviourTree() : root(new Root) {}
	void setRootChild(Node* rootChild) const { root->setChild(rootChild); }
	bool run() const { return root->run(); }
	
};


class Action : public BehaviourTree::Node 
{
private:
	BehaviourTree bt;
	std::string name;
	bool isThereItem;
public:
	Action(BehaviourTree& newbt, std::string newName, bool isthereItem) : name(newName), bt(newbt), isThereItem(isthereItem) {}
private:
	virtual bool run() override 
	{
		if (isThereItem)
		{
			bt.leafNodeToRun = name;
			return true;
		}
		else
			return false;
	}
};
