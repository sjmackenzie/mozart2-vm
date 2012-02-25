// Copyright © 2011, Université catholique de Louvain
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// *  Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// *  Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __REFERENCE_H
#define __REFERENCE_H

#ifndef MOZART_GENERATOR

#include "store.hh"
#include "gctypes.hh"

#include <iostream>

///////////////
// Reference //
///////////////

void Reference::gCollect(GC gc, Node& from, StableNode& to) const {
  Node& destNode = dereference(from);

  if (OzDebugGC) {
    cerr << " \\-> gc " << &destNode << " of type " << destNode.type->getName();
    cerr << "   \tto node " << &to << endl;
  }

  destNode.type->gCollect(gc, destNode, to);
  destNode.make<GCedToStable>(gc->vm, &to);
}

void Reference::gCollect(GC gc, Node& from, UnstableNode& to) const {
  Node& destNode = dereference(from);

  if (OzDebugGC) {
    cerr << " \\-> gc " << &destNode << " of type " << destNode.type->getName();
    cerr << "   \tto node " << &to << endl;
  }

  destNode.type->gCollect(gc, destNode, to);
  destNode.make<GCedToUnstable>(gc->vm, &to);
}

#endif // MOZART_GENERATOR

#endif // __REFERENCE_H