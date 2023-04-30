//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINETYPE_H
#define SCHEDULING_MACHINETYPE_H


class MachineType {
protected:
    long id;
public:
    explicit MachineType(long id);
    [[nodiscard]] long getId() const;
};


#endif //SCHEDULING_MACHINETYPE_H
