#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;


#define ScreenWidth 2000
#define ScreenHeight 2000

#define ShapeWidth 1
#define ShapeHeight 1

class Node
{
private:
	int data;
	Node* next;
public:
	friend class queue;
	Node()
	{
		next = nullptr;
	}
};
class queue
{
private:
	Node* head;
	Node* tail;
	Node* startfromhere;
	int size;
	int k;
public:
	queue(int size, int k)
	{
		this->size = size;
		this->k = k;
		head = new Node;
		tail = new Node;
	}
	void Insert_at_tail(int i)
	{
		if (head->data == NULL)
		{
			head->data = i;
			head->next = nullptr;
			startfromhere = head;
		}
		else if (head->next == nullptr)
		{
			tail->data = i;
			head->next = tail;
			tail->next = head;
		}
		else
		{
			Node* n = new Node;
			n->data = i;
			n->next = head;
			Node* temp = tail;
			tail = n;
			temp->next = tail;
		}
	}
	void enqueue_all()
	{
		for (int i = 1; i <= size;i++)
		{
			Insert_at_tail(i);
		}
	}
	int dequeue()
	{
		if (size > 1)
		{
			int num;
			Node* executehim = startfromhere;
			for (int i = 1; i < k;i++)
			{
				executehim = executehim->next;
				startfromhere = startfromhere->next;
			}
			startfromhere = startfromhere->next;

			num = executehim->data;
			Node* curr = head;
			while (curr->next != executehim)
			{
				curr = curr->next;
			}
			curr->next = curr->next->next;
			if (executehim == head)
			{
				head = head->next;
			}
			delete executehim;
			executehim = nullptr;
			size--;
			return num;
		}
		else
		{
			cout << "Only one man left." << endl;
			return 0;
		}
	}
	void print()
	{
		Node* curr = head;
		cout << curr->data << "->";
		curr = curr->next;
		while (curr != head)
		{
			cout << curr->data << "->";
			curr = curr->next;
		}
		cout << endl;
	}
};

int main()
{
	int ppl = 0, n=0;
	cout << "Enter number of ppl:" << endl;
	cin >> ppl;
	cout << "Enter n:" << endl;
	cin >> n;
	queue game(ppl, n);
	game.enqueue_all();
	sf::Text text;
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Josephus Problem");
    window.setKeyRepeatEnabled(false);
    sf::Texture ptexture;
    sf::Sprite manImage;
        if (!ptexture.loadFromFile("man.png"))
            cout << "Could not load the image file." << endl;

        manImage.setTexture(ptexture);

		int number = -1, num=0;
		int x2=0;
		cout << "Press Enter." << endl;
			while (window.isOpen())
			{
				sf::Event event;

				while (window.pollEvent(event))
				{
					window.clear();
					switch (event.type)
					{
					case sf::Event::Closed :
							window.close();
						break;
					case sf :: Event :: KeyPressed :
						if (event.key.code == sf::Keyboard::Enter)
						{
							int x = 70+ x2, y = 0, y2= 70;
							x2 = 0;
							if (number != 0)
							{
								game.print();
								number = game.dequeue();
								num = 0;
								while (num < ppl)
								{
									manImage.move(x, y);
									x = 70;
									window.draw(manImage);
									num++;
									x2 = x2 - 70;
								}
								if (num == ppl)
								{
									window.display();
									num++;
								}
								ppl--;
							}
						}
					}
				}	
			}
	   return 0;
}

