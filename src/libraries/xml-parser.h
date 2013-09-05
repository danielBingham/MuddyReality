
#ifndef XML_PARSER_H_ 
#define XML_PARSER_H_ 

class XMLParser {
	friend class XMLDocument;
	friend class XMLNode;

	public:

		XMLDocument parse(String file);

	protected:

};

class XMLDocument {
	friend class XMLNode;
	
	public:

	protected:
		String text;
		XMLNode *root;

};

class XMLNode {

	public:

	protected:
		int open_tag_start;
		int open_tag_end;
	
		int closing_tag_start;
		int closing_tag_end;

		XMLDocument *document;
		XMLNode *children;
};

#endif /* XML_PARSER_H_ */
