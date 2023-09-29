#pragma once

#include <functional>
#include <Tree.hpp>

// Allows declarative and conditional tree construction
// More precisely, TreeConstructor a b -> TreeNode b, where there is a function a -> [b]
template <typename In, typename Out> struct TreeConstructor {
	std::function<std::vector<Out>(In)> nodesToAttach;
	std::vector<TreeConstructor<In, Out>> children;
};

template <typename In, typename Out>
void constructTree(TreeConstructor<In, Out> consNode, TuxClocker::TreeNode<Out> &node, In in) {
	for (auto &newNode : consNode.nodesToAttach(in)) {
		// Attach wanted child
		auto treeNode = TuxClocker::TreeNode<Out>{newNode};
		node.appendChild(treeNode);
		for (auto &child : consNode.children)
			// We need pointer since node.children() just gives a copy
			constructTree(child, node.childrenPtr()->back(), in);
	}
}
