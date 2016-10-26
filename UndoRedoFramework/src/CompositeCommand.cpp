/*
 * CompositeCommand.cpp
 *
 *  Created on: 19.02.2015
 *      Author: Gerd
 */

#include "../include/CompositeCommand.h"
#include "../include/UndoRedoManager.h"

CompositeCommand::CompositeCommand(UndoRedoManager && urMngr)
: urMngr( std::move(urMngr).clone())
//: urMngr( urMngr.clone())
{ }

CompositeCommand::CompositeCommand(CompositeCommand && rhs)
: urMngr( std::move(rhs.urMngr) )
{  }

std::unique_ptr<Command> CompositeCommand::clone() const&
{
	// ugly hack, but we must implement all virtual Operations
	// CompositeCommands cannot be copied
	throw std::logic_error("Operation not supported");
}
std::unique_ptr<Command> CompositeCommand::clone() &&
{
	return std::unique_ptr<Command>( new CompositeCommand( std::move(*this) ));
}
CompositeCommand::~CompositeCommand() {
	//definition wird wegen unique_ptr<..> urMngr ben�tigt
}

/**
 * f�gt das Command c in den internen CommandManager
 * (UndoRedoHandler.doit(Command c) ein
 *
 * @param c
 */
void CompositeCommand::doIt(Command&& c) {
	urMngr->doIt( std::move(c) );
}
void CompositeCommand::doIt(Command const& c) {
	urMngr->doIt(c);
}
void CompositeCommand::doIt(SmartPointer&& c) {
	urMngr->doIt( std::move(c) );
}
/**
 * f�hrt die Commands wieder aus
 * nach dem sie r�ckg�ngig gemacht wurden
 * @see undo()
 *
 * @throws Exception
 */
void CompositeCommand::doIt() {
	while (urMngr->canRedo()) {
		urMngr->redo();
	}
}
/**
 * Commands m�ssen in der umgekehrten Reihenfolge r�ckg�ngig gemacht werden,
 * wie sie ausgef�hrt wurden! Dazu wird ein UndoRedoManager benutzt.
 *
 * @directed true
 * @supplierRole Command Manager
 */
void CompositeCommand::undo() {
	while (urMngr->canUndo()) {
		urMngr->undo();
	}
}

