Cocker - container management system, same as Docker / Podman, written for study purposes.
Name comes from first letter of implementation language C++ and other part from name of the parallel technology - Docker.
Hope that this name is acceptable...

МЫ хотим глубоко разобраться в принциах работы систем управления контейнерами, чтобы, как минимум, уметь грамотно ими пользоваться, решать нетривиальные задачи в этой области, и как максимум, иметь опыт в реализации таких систем, если это когда-нибудь понадобится.

Примеры существующих систем:

* [Docker](https://www.docker.com/)

* [Podman](https://podman.io/)

* [LXC](https://linuxcontainers.org/lxc/introduction/)

* [ContainerD](https://containerd.io/)

Лучший стособ глубоко разобраться - написать такую систему самому.

Рабочий репозиторий - [здесь](https://github.com/AlexandrBirman/Cocker).

Черновой план действий:

1) Легкое введение [тут](https://dorny.github.io/docker-deep-dive/#/);

2) Реализовать все то, что написано [здесь](https://cesarvr.github.io/post/2018-05-22-create-containers/) на C++;
   
   - Дополнительно почитать [это](http://ifeanyi.co/posts/linux-namespaces-part-1/) (все части);
   - [cgroups](https://pierrchen.blogspot.com/2018/04/container-deep-dive-2-linux-cgroups.html);
   - еще [cgroups](https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/6/html/resource_management_guide/ch01);

3) Продумать дизайн и интерфейс низкоуровневой системы управления контейнерами на основе существующих аналогов, таких как [runc](https://github.com/opencontainers/runc) и [containerd](https://github.com/containerd/containerd);

4) Проработать систему в соответствии со спецификацией стандарта [OCI](https://opencontainers.org/about/overview/) . Это позволит работать с образами докера и других систем;

5) Подключить ралзичные оптимизации типа [OverlayFS](https://docs.docker.com/storage/storagedriver/overlayfs-driver/);

6) Проработать общий дизайн и интерфейс системы и реализовать его.
