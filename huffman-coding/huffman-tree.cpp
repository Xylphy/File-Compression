#include "huffman-tree.h"
#include <utility>

HuffmanTree::Node::Node(char data, size_t freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

HuffmanTree::Node::Node(char data, size_t freq, Node *left, Node *right) :
	data(data), freq(freq), left(left), right(right)
{
}

HuffmanTree::Node::Node(const Node &other) :
	data(other.data), left(other.left ? new Node(*other.left) : nullptr),
	right(other.right ? new Node(*other.right) : nullptr), freq(other.freq)
{
}

HuffmanTree::Node::Node(Node &&other) noexcept :
	data(std::exchange(other.data, 0)), left(std::exchange(other.left, nullptr)),
	right(std::exchange(other.right, nullptr)), freq(std::exchange(other.freq, 0))
{
}

HuffmanTree::Node &HuffmanTree::Node::operator=(const Node &other)
{
	if (this != &other)
	{
		Node temp(other);
		std::swap(data, temp.data);
		std::swap(left, temp.left);
		std::swap(right, temp.right);
		std::swap(freq, temp.freq);
	}
	return *this;
}

HuffmanTree::Node &HuffmanTree::Node::operator=(Node &&other) noexcept
{
	if (this != &other)
	{
		delete left;
		delete right;
		data = std::exchange(other.data, 0);
		left = std::exchange(other.left, nullptr);
		right = std::exchange(other.right, nullptr);
		freq = std::exchange(other.freq, 0);
	}
	return *this;
}

HuffmanTree::Node::~Node()
{
	delete left;
	delete right;
}
