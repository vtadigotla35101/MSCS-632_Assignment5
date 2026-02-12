"======================================================================
| Ride Sharing System - GNU Smalltalk Implementation
======================================================================"

"--- 1. Ride Base Class ---"
Object subclass: Ride [
    | rideID distance |
    
    Ride class >> new: id dist: d [
        ^ (super new) init: id dist: d
    ]

    init: id dist: d [
        rideID := id.
        distance := d.
    ]

    calculateFare [ ^ distance * 1.5 ]
    
    rideDetails [ 
        ^ 'Ride ID: ', rideID, ' | Distance: ', distance printString, ' miles'
    ]
]

"--- 2. Specific Ride Subclasses (Polymorphism) ---"
Ride subclass: StandardRide [
    calculateFare [ ^ distance * 1.0 ]
    
    rideDetails [ 
        ^ 'Standard ', super rideDetails 
    ]
]

Ride subclass: PremiumRide [
    calculateFare [ ^ (distance * 3.0) + 5.0 ]
    
    rideDetails [ 
        ^ 'Premium  ', super rideDetails 
    ]
]

"--- 3. Driver Class (Encapsulation) ---"
Object subclass: Driver [
    | name assignedRides |
    
    Driver class >> new: aName [
        ^ (super new) init: aName
    ]

    init: aName [
        name := aName.
        assignedRides := OrderedCollection new.
    ]

    addRide: aRide [ 
        assignedRides add: aRide 
    ]

    getDriverInfo [
        Transcript show: '=== Driver Profile ==='; cr.
        Transcript show: 'Name: ', name; cr.
        Transcript show: 'Completed Rides:'; cr.
        assignedRides do: [ :r | 
            Transcript show: '  - '; show: r rideDetails; 
                       show: ' | Fare: $'; 
                       show: r calculateFare printString; cr.
        ].
        Transcript cr.
    ]
]

"--- 4. Rider Class ---"
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> new: id name: aName [
        ^ (super new) init: id name: aName
    ]

    init: id name: aName [
        riderID := id.
        name := aName.
        requestedRides := OrderedCollection new.
    ]

    requestRide: aRide [
        requestedRides add: aRide.
    ]

    viewRides [
        Transcript show: '=== Rider History: ', name, ' (', riderID, ') ==='; cr.
        requestedRides do: [ :ride |
            Transcript show: '  - '; show: ride rideDetails; cr.
        ].
        Transcript cr.
    ]
]

"--- 5. System Functionality (Main Execution Block) ---"
| myDriver myRider systemRides |

"Initialize Objects"
myDriver := Driver new: 'Vishnu'.
myRider := Rider new: 'R-99' name: 'Tadigotla'.

"Create a collection of different ride types to demonstrate polymorphism"
systemRides := OrderedCollection new.
systemRides add: (StandardRide new: 'Trip-STD' dist: 12.5).
systemRides add: (PremiumRide new: 'Trip-PRE' dist: 25.0).
systemRides add: (StandardRide new: 'Trip-STD2' dist: 8.0).

"Distribute rides through the system"
systemRides do: [ :each | 
    myRider requestRide: each.
    myDriver addRide: each.
].

"Display Information polymorphically"
myRider viewRides.
myDriver getDriverInfo.