#pragma once

#include <functional>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>

class HuffmanCodes
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

public:
	HuffmanCodes(std::string text);
	~HuffmanCodes();

	void build();
	std::string decode(const std::string &code) const;

private:
	std::string text;
	std::priority_queue<Node *, std::vector<Node *>, std::function<bool(const Node *, Node *)>> pq;
	std::unordered_map<std::string, char> codes;

	void buildCodes(Node *root, std::string &&code);

	friend std::ostream &operator<<(std::ostream &os, const HuffmanCodes &hc);
};
