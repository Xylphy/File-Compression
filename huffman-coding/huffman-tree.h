#pragma once

#include <cstddef>

class HuffmanTree
{
	struct Node
	{
		char data;
		Node *left, *right;
		size_t freq;

		Node(char data, size_t freq);
		Node(char data, size_t freq, Node *left, Node *right);

		Node() = default;
		Node(const Node &other);
		Node(Node &&other) noexcept;
		Node &operator=(const Node &other);
		Node &operator=(Node &&other) noexcept;
		~Node();
	};
};
