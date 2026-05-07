#ifndef STRINGIFY_H
#define STRINGIFY_H

#define __stringify_1(x...) #x
#define __stringify(x...)   __stringify_1(x)

#endif /* STRINGIFY_H */