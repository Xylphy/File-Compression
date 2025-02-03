#include "huffman_codes.h"
#include <string>
#include <unordered_map>
#include <utility>

HuffmanCodes::HuffmanCodes(std::string text) :
	pq([](const Node *a, const Node *b) -> bool { return a->freq > b->freq; }), text(std::move(text))
{
}

HuffmanCodes::Node::Node(char data, size_t freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}

HuffmanCodes::Node::Node(char data, size_t freq, Node *left, Node *right) :
	data(data), freq(freq), left(left), right(right)
{
}

HuffmanCodes::Node::Node(const Node &other) :
	data(other.data), left(other.left ? new Node(*other.left) : nullptr),
	right(other.right ? new Node(*other.right) : nullptr), freq(other.freq)
{
}

HuffmanCodes::Node::Node(Node &&other) noexcept :
	data(std::exchange(other.data, 0)), left(std::exchange(other.left, nullptr)),
	right(std::exchange(other.right, nullptr)), freq(std::exchange(other.freq, 0))
{
}

HuffmanCodes::Node &HuffmanCodes::Node::operator=(const Node &other)
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

HuffmanCodes::Node &HuffmanCodes::Node::operator=(Node &&other) noexcept
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

HuffmanCodes::Node::~Node()
{
	delete left;
	delete right;
}

void HuffmanCodes::build()
{
	if (text.empty())
		return;

	std::unordered_map<char, int> freq;

	for (const char &c : text)
		freq[c]++;

	for (const std::pair<const char, const int> &p : freq)
		pq.emplace(new Node(p.first, p.second));

	while (pq.size() > 1)
	{
		Node *left = pq.top();
		pq.pop();
		Node *right = pq.top();
		pq.pop();

		pq.emplace(new Node(0, left->freq + right->freq, left, right));
	}

	buildCodes(pq.top(), "");
}

std::string HuffmanCodes::decode(const std::string &code) const
{
	if (codes.empty())
		return "";

	std::string decoded;

	size_t left = 0, right = 1;

	while (right <= code.size())
	{
		auto it = codes.find(code.substr(left, right - left));

		if (it != codes.end())
		{
			decoded += it->first;
			left = right;
		}

		right++;
	}

	return std::move(decoded);
}

void HuffmanCodes::buildCodes(Node *root, std::string &&code)
{
	if (root->data)
	{
		codes[code] = root->data;
		return;
	}

	buildCodes(root->left, code + '0');
	buildCodes(root->right, code + '1');
}

std::ostream &operator<<(std::ostream &os, const HuffmanCodes &hc)
{
	for (const std::pair<const std::string, char> &p : hc.codes)
		os << p.second << " : " << p.first << std::endl;
	return os;
}

HuffmanCodes::~HuffmanCodes()
{
	while (!pq.empty())
	{
		delete pq.top();
		pq.pop();
	}
}
