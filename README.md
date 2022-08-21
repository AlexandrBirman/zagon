# Zagon

Zagon - minimalistic daemonless container manager (in future...).

Developed for study purposes.

## Docs

[ENG]() (empty yet)

[RUS]() (empty yet)

## Build

Generate default build files, build default goal from them and run tests:
```sh
mkdir -p build
cmake -B ./build
cmake --build ./build --target all
```

Run project:
```sh
./build/zagon
```

Also available is bash script that build and run prject:
```sh
./run.sh
```


## Roadmap

- [TODO] -  OCI compatible container runtime, same as runc, crun.
  Main goal - isolation and secutiry. (runz)
- [TODO] - Image builder, same as Buildah.
- [TODO] - Daemonless container manager, same as Podman.

