//  Copyright (C) 2005-2012 Robert Kooima
//
//  THUMB is free software; you can redistribute it and/or modify it under
//  the terms of  the GNU General Public License as  published by the Free
//  Software  Foundation;  either version 2  of the  License,  or (at your
//  option) any later version.
//
//  This program  is distributed in the  hope that it will  be useful, but
//  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
//  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
//  General Public License for more details.

#ifndef SPH_CRATER_HPP
#define SPH_CRATER_HPP

#include <string>

//-----------------------------------------------------------------------------

class sph_crater
{
public:

    sph_crater(const std::string&);
   ~sph_crater();

    void draw(const double *);

private:

};

//-----------------------------------------------------------------------------

#endif