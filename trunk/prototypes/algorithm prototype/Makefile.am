#############################################################################
#
#    phylopp.cpp: library implementation to process phylogenetic trees.
#    Copyright (C) 2009  Daniel Gutson, FuDePAN
#
#    phylopp.h is part of phylopp.
#
#    phylopp is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    phylopp is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with phylopp.  If not, see <http://www.gnu.org/licenses/>.
#


noinst_PROGRAMS=tree-places

lib_LTLIBRARIES=libphylopp.la

#Sources
libphylopp_la_SOURCES=phylopp.cpp phylopp.h

tree_places_SOURCES=tree-places.cpp phylopp.h
tree_places_LDADD=libphylopp.la
tree_places_DEPENDENCIES = libphylopp.la


EXTRA_DIST= places.dat tree.dat CHANGELOG CONTRIBUTORS gpl.txt README

