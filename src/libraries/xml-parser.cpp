
#include <xml-parser.h>

/**
 *
 */
XMLDocument *XMLParser::parse(String text) {
	XMLDocument *document = new XMLDocument();
	this.character = 0;

	document->root = new XMLNode();
	for (XMLNode *node; node != NULL; node = this.parse_node(text, root)) {	
		document->root->addNode(node);
	}

	return document;
}

/**
 *
 */
XMLNode *XMLParser::parse_node(String text, XMLNode *parent) {
	int open_character = -1;
	XMLNode *node = new XMLNode();

	for(; this.character < text.length(); this.character++) {

		// Tag opening
		if (text[this.character] == '<' && open_character == -1) {
	
			// We found a closing tag.
			if (text[this.character+1] == '/') {
			
			}
		
		} else if (text[this.character] == '<') {
			XMLNode *child = this.parse_node(text,parent); 
	
		// Tag closing	
		} else if (text[this.character] == '>') {
			return node;	
		}
	}
}

		
XMLDocument::XMLDocument() {}
XMLDocument::~XMLDocument() {
	delete this.root;
}

XMLNode::XMLNode() {}
XMLNode::~XMLNode() {
	for(int i = 0; i < this.number_of_children; i++) {
		delete this.children[i];
	}

	delete [] this.children;	
}


