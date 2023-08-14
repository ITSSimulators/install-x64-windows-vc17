/*
    Copyright (C) 2008 Seeing Machines Ltd. All rights reserved.

    This file is part of the CoreData API.

    This file may be distributed under the terms of the SM Non-Commercial License
    Agreement appearing in the file LICENSE.TXT included in the packaging
    of this file.

    This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
    WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

    Further information about the CoreData API is available at:
    http://www.seeingmachines.com/

*/
#ifndef SM_COREDATA_EOD_IDGENERATOR_H
#define SM_COREDATA_EOD_IDGENERATOR_H

#include <bitset>

namespace sm
{
    namespace eod
    {
        namespace io
        {
            namespace detail
            {
                template<class IDType, int Range>
                class IDGenerator
                {
                public:
                    IDGenerator() : _nextID(0)
                    {
                    }

                    IDType reserveID()
                    {
                        while (_IDs.test(_nextID)) //TODO: potential infinite loop
                        {
                            ++_nextID;
                            if (static_cast<std::size_t>(_nextID) >= _IDs.size())
                                _nextID = 0;
                        }

                        _IDs.set(_nextID, 1);
                        return _nextID++;
                    }

                    void releaseID(IDType& id)
                    {
                        _IDs.set(id, 0);
                    }

                private:
                    typedef std::bitset<Range> IDStore;

                    IDStore _IDs;
                    IDType _nextID;
                };
            }
        }
    }
}

#endif //SM_COREDATA_EOD_IDGENERATOR_H

