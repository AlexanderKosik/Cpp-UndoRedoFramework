#ifndef UNDOREDOMANAGERIMPLBYINHERITANCE_H
#define UNDOREDOMANAGERIMPLBYINHERITANCE_H

#include <UndoRedoFramework/ByInheritance/UndoRedoStackImpl.h>
#include <UndoRedoFramework/ByInheritance/UndoRedoManager.h>
#include <UndoRedoFramework/Command.h>

#include <stack>
#include <memory>

namespace UndoRedoFramework{
namespace ByInheritance{

class UndoRedoManagerImpl : public UndoRedoStackImpl, public UndoRedoManager
{

public:

	UndoRedoManagerImpl();
	UndoRedoManagerImpl(UndoRedoManagerImpl && rhs);

	//for non copyable commands
	//for copyable commands
	//for SmartPointers
//	virtual void doIt(Command && command) override;
//	virtual void doIt(Command const& command) override;

	virtual void doIt(SmartPointer && command) override;

//	virtual bool isUndoable() const override;
	virtual void undo() override;

//	virtual bool isRedoable() const override;
	virtual void redo() override;
	
	virtual bool isModified() const override;
	virtual void resetModified() override;
//	virtual std::unique_ptr<UndoRedoManager> clone() && override;

//	virtual void clear() override;
private:
	int modifications;
};

}} // end namespace
#endif //UNDOREDOMANAGERIMPLBYINHERITANCE_H
