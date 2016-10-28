#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

template<typename T>
class DualLinkList
{
private:
	class Node
	{
	public:
		T data;
		Node* prev;
		Node* next;

		Node(T const& data, Node* prev = nullptr, Node* next = nullptr)
		{
			this->data = data;
			this->prev = prev;
			this->next = next;
		}
		~Node()
		{
			delete prev;
			delete next;
		}
	};

	Node* root;
	size_t nrOfNodes;
    
    void deleteNode(Node* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = nullptr;
        node->prev = nullptr;
        delete node;
    }
    
public:
	DualLinkList()
	{
		this->root = nullptr;
		this->nrOfNodes = 0;
	}

	~DualLinkList()
	{
		delete this->root;
	}
    
    void addFirst(T const& data)
    {
        if (this->root != nullptr)
        {
            this->root = new Node(data, this->root->prev, this->root);
            this->root->next->prev = this->root;
            this->root->prev->next = this->root;
        }
        else
        {
            this->root = new Node(data);
            this->root->next = this->root;
            this->root->prev = this->root;
        }
        this->nrOfNodes++;
    }

	void addLast(T const& data)
	{
        if (this->root != nullptr)
        {
            this->root->prev = new Node(data, this->root->prev, this->root);
            this->root->prev->prev->next = this->root->prev;
        }
        else
        {
            this->root = new Node(data);
            this->root->next = this->root;
            this->root->prev = this->root;
        }
        this->nrOfNodes++;
	}
    
    void removeAt(size_t index)
    {
        if (index >= this->nrOfNodes)
        {
            throw new Exception("Index out of range");
        }
        
        Node* walker = this->root;
        
        if (index == 0)
        {
            this->root = walker->next;
        }
        else
        {
            for (size_t i = 0; i < index; i++) {
                walker = walker->next;
            }
        }
        
        this->deleteNode(walker);
        this->nrOfNodes--;
        
        if (this->nrOfNodes == 0)
        {
            this->root = nullptr;
        }
    }
};

#endif // !DUALLINKLIST_H
