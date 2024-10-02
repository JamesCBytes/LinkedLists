// Author: Connor James
// Assignment: Homework 2
// File: Definitions of declartions for link list implentation

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const{
	// enforce precondition
	if((position >= 1) && (position <= itemCount)){
		// Count from the beginning of the chain
		Node<ItemType>* curPtr = headPtr;
		for (int skip = 1; skip < position; skip++){
			curPtr = curPtr->getNext();
		}
		return curPtr;
	}
	return nullptr;
} 

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0){}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList){
	itemCount = aList.itemCount;
	for(int i = itemCount; i > 0; i--){ // going backwards, add each node to the beginning of our new list
		ItemType temp = aList.getNodeAt(i)->getItem(); // make a temp copy of the item stored in the original node
		insert(1, temp);
	}
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const{
	return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const{
	return itemCount;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry){
 	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if(ableToInsert){
		Node<ItemType>* newPtr = new Node<ItemType>(newEntry);
		if(newPosition == 1){ 
			newPtr->setNext(headPtr); 
			headPtr = newPtr; 
		}else{
			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
			newPtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newPtr); 
		}
		itemCount++;
	}
    return ableToInsert;
}


template<class ItemType>
bool LinkedList<ItemType>::remove(int position){
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove){
		Node<ItemType>* ptrToDelete = nullptr;
		if (position == 1){
			// Remove the first node in the chain
			ptrToDelete = headPtr; // Save pointer to node 
			headPtr = headPtr->getNext();// save pointer to next node
		}
		else{
			// Find node that is before the one to remove
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			// Point to node to remove
			ptrToDelete = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the prior node with the one after
			prevPtr->setNext(ptrToDelete->getNext());
		}

		ptrToDelete->setNext(nullptr);
		delete ptrToDelete;
		ptrToDelete = nullptr;
		itemCount--; // Decrease count of entries
	}
	return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear(){
	for(int i = itemCount; i > 0; i--){ // remove from end to beginning
		remove(i);
	}

}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const {
    bool ableToGet = (position >= 1) && (position <= itemCount);
	if(ableToGet){
		Node<ItemType>* nodePtr = getNodeAt(position);
    	ItemType temp;
		temp = nodePtr->getItem();
    	return temp;
	}
	throw "item not found";
} 

template<class ItemType>
ItemType LinkedList<ItemType>::replace(int position, const ItemType& newEntry){
	// enforce precondition
	bool ableToReplace = (position >= 1) && (position <= itemCount);
	if (ableToReplace){
		Node<ItemType>* nodePtr = getNodeAt(position);
		ItemType oldEntry = nodePtr->getItem();
		nodePtr->setItem(newEntry);	
		return oldEntry;	
	} 
	throw "Item not found";
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList(){
	clear();
} 
