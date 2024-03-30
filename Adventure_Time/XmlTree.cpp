#include "XmlTree.h"

#include <fstream>
#include <sstream>
#include <stack>
#include <iomanip>
#include <iostream>
using namespace std;


void XmlTree::parse(const char* file_name)
{
	ifstream fin(file_name);
	string s;
	vector<string> xml;

	getline(fin, s);
	if (s.substr(0, 2) != std::string("<?"))
	{
		int i = 0;
		while (s[i] == ' ')
		{
			++i;
		}
		s.erase(0, i);
		xml.push_back(s);
	}

	while (getline(fin, s))
	{
		int i = 0;
		while (s[i] == ' ')
		{
			++i;
		}
		s.erase(0, i);
		xml.push_back(s);
	}

	//for update parent and sibling
	stack<XmlNode*> stack_XmlNode;

	for (size_t i = 0; i < xml.size(); ++i)
	{
		string temp = xml[i];
		temp.erase(remove(temp.begin(), temp.end(), '	'), temp.end());
		temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());
		if (temp.front() == ' ')
		{
			string::iterator ite = temp.begin();
			while (*ite == ' ')
			{
				++ite;
			}
			temp.erase(remove(temp.begin(), ite, ' '), temp.end());
		}
		//cout << temp << '\n';

		if (temp.substr(0, 2) != "</")
		{
			if (temp.front() == '<')
			{
				stringstream ss(temp);
				char c;
				string t;
				ss >> c >> t;

				XmlNode* p_new_XmlNode = new XmlNode(t);

				if (stack_XmlNode.size() > 0)
				{
					XmlNode* parent = stack_XmlNode.top();
					if (parent->child.size() > 0)
					{
						XmlNode* last_child = parent->child.back();
						last_child->next_sib = p_new_XmlNode;
						p_new_XmlNode->prev_sib = last_child;
					}
					parent->child.push_back(p_new_XmlNode);
					p_new_XmlNode->parent = parent;
				}
				else
				{
					mRoot = p_new_XmlNode;
				}

				stack_XmlNode.push(p_new_XmlNode);

				if (ss.eof() == false)
				{
					string attribute;
					while (ss >> attribute)
					{
						string::iterator ite = find(attribute.begin(), attribute.end(), '=');

						string property = string(attribute.begin(), ite);
						string value = string(++ite, attribute.end());

						value.erase(remove(value.begin(), value.end(), '"'), value.end());
						if (value.back() == '/')
						{
							stack_XmlNode.pop();
							value.pop_back();
						}

						//cout << property << ' ' << value << '\n';
						p_new_XmlNode->attribute_set[property] = value;
					}
				}
				else
				{

				}
			}
			else
			{
				XmlNode* element = stack_XmlNode.top();

				element->text ="";
				while (xml[i].front() != '<')
				{
					element->text += xml[i];
					++i;
				}
				--i;
			}

		}
		else
		{
			stack_XmlNode.pop();
		}
	}
}

bool XmlNode::takeAttribute(const string& property, int* x)
{
	if (attribute_set.find(property) != attribute_set.end())
	{
		*x = stoi(attribute_set[property]);
	}
	else
	{
		return false;
	}
	return true;
}
bool XmlNode::takeAttribute(const string& property, string* s)
{
	if (attribute_set.find(property) != attribute_set.end())
	{
		*s = attribute_set[property];
	}
	else
	{
		return false;
	}
	return true;
}


void travel(XmlNode* parent)
{
	if (parent->child.size() == 0)
	{
		delete parent;
		return;
	}
	for (XmlNode* ite : parent->child)
	{
		travel(ite);
	}
	delete parent;
}

XmlTree::~XmlTree()
{
	travel(mRoot);
}