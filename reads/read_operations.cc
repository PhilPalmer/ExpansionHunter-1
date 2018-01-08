//
// Expansion Hunter
// Copyright (c) 2016 Illumina, Inc.
//
// Author: Egor Dolzhenko <edolzhenko@illumina.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "reads/read_operations.h"

#include <algorithm>
#include <string>

#include "common/seq_operations.h"

using std::string;

namespace reads {

void ReorientRead(const StrandClassifier& classifier, Read& read) {
  const bool is_orientation_correct =
      classifier.IsForwardOriented(read.Bases());

  if (!is_orientation_correct) {
    const string oriented_bases = ReverseComplement(read.Bases());
    string oriented_quals = read.Quals();
    std::reverse(oriented_quals.begin(), oriented_quals.end());
    read.SetCoreInfo(read.FragmentId(), oriented_bases, oriented_quals);
  }
}
}  // namespace reads