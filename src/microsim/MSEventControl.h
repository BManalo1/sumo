/***************************************************************************
                          MSEventControl.h  -  Coordinates
                          time-dependant events
                             -------------------
    begin                : Mon, 12 Mar 2001
    copyright            : (C) 2001 by ZAIK http://www.zaik.uni-koeln.de/AFS
    author               : Christian Roessel
    email                : roessel@zpr.uni-koeln.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MSEventControl_H
#define MSEventControl_H

// $Log$
// Revision 1.2  2002/10/16 16:39:02  dkrajzew
// complete deletion within destructors implemented; clear-operator added for container; global file include
//
// Revision 1.1  2002/10/16 14:48:26  dkrajzew
// ROOT/sumo moved to ROOT/src
//
// Revision 1.2  2002/07/31 17:33:00  roessel
// Changes since sourceforge cvs request.
//
// Revision 1.4  2002/07/30 15:20:20  croessel
// Made previous changes compilable.
//
// Revision 1.3  2002/07/26 11:44:29  dkrajzew
// Adaptation of past event execution time implemented
//
// Revision 1.2  2002/07/26 11:05:12  dkrajzew
// sort criterium debugged; addEvent now returns a bool; problems with
// parallel insertion of items with the execute-method debugged
//
// Revision 1.1.1.1  2002/04/08 07:21:23  traffic
// new project name
//
// Revision 2.0  2002/02/14 14:43:15  croessel
// Bringing all files to revision 2.0. This is just cosmetics.
//
// Revision 1.7  2002/02/05 13:51:51  croessel
// GPL-Notice included.
// In *.cpp files also config.h included.
//
// Revision 1.6  2002/01/10 11:52:43  croessel
// Method addEvent() added and implemented. execute() implemented.
//
// Revision 1.5  2001/12/19 17:04:35  croessel
// using namespace std replaced by std::
// Copy-ctor and assignment-operator moved to private.
//
// Revision 1.4  2001/11/15 17:12:14  croessel
// Outcommented the inclusion of the inline *.iC files. Currently not
// needed.
//
// Revision 1.3  2001/11/14 11:45:53  croessel
// Resolved conflicts which appeared during suffix-change and
// CR-line-end commits.
//
// Revision 1.2  2001/07/16 12:55:46  croessel
// Changed id type from unsigned int to string. Added string-pointer
// dictionaries and dictionary methods.
//
// Revision 1.1.1.1  2001/07/11 15:51:13  traffic
// new start
//

#include <utility>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include "MSNet.h"

class Command;

/**
 */
class MSEventControl
{
public:
    /// Events that should be executed at time.
    typedef std::pair< Command*, MSNet::Time > Event;

    /// what to do on false time
    enum AdaptType { ADAPT_AFTER_EXECUTION };

    /// Sort-criterion for events.
    class EventSortCrit
    {
    public:
        bool operator() ( const Event& e1, const Event& e2 ) const;
    };

    /// Use only this constructor.
    MSEventControl( std::string id );

    /// Destructor.
    ~MSEventControl();

    // Add an Event.
    bool addEvent( Command* operation, MSNet::Time execTime, AdaptType type );

    /** Executes time-dependant commands, like switching
        traffic-lights, writing output, etc. */
    void execute( MSNet::Time time );

    /** Inserts eventcontrol into the static dictionary and returns true
        if the key id isn't already in the dictionary. Otherwise returns
        false. */
    static bool dictionary( std::string id, MSEventControl* event );
    /** Returns the MSEdgeControl associated to the key id if exists,
        otherwise returns 0. */
    static MSEventControl* dictionary( std::string id );

    /** Clears the dictionary */
    static void clear();

//      friend class MSNet;
protected:

private:
//      void setTime( MSNet::Time time );

private:
//      MSNet::Time myTime;

    /// Unique ID.
    std::string myID;

    /// Container for time-dependant events, e.g. traffic-light-change.
    typedef std::priority_queue< Event, std::vector< Event >,
                                 EventSortCrit > EventCont;

    /// Event-container, holds executable events.
    EventCont myEvents;

    /// Static dictionary to associate string-ids with objects.
    typedef std::map< std::string, MSEventControl* > DictType;
    static DictType myDict;

    /// Default constructor.
    MSEventControl();

    /// Copy constructor.
    MSEventControl(const MSEventControl&);

    /// Assignment operator.
    MSEventControl& operator=(const MSEventControl&);
};


/**************** DO NOT DECLARE ANYTHING AFTER THE INCLUDE ****************/

//#ifndef DISABLE_INLINE
//#include "MSEventControl.icc"
//#endif

#endif

// Local Variables:
// mode:C++
// End:
