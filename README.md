# schroot

Lightweight virtualisation tool


## End of life

As of June 2022, schroot has been officially retired, and users should
migrate to a supported alternative.  Unofficially, schroot has not been
actively maintained for several years and it has been effectively
obsoleted by more capable alternatives for well over a decade.  Users
are advised to switch to one of these alternatives.

The last stable release is still available on the `schroot-1.6` branch.
The `master` branch still contains unreleased development work.

schroot will continue to function, but maintenance has ended.  GitLab
merge requests will no longer be accepted, and there will be no further
software releases.


## Alternatives

Since schroot was developed, a whole host of solutions have appeared, most of
which long reached and exceeded feature-parity.  It is highly recommended to
switch to a supported alternative.

* Docker.  For better or worse, it is the established standard.  It is
  recommended for package building.  Whether you use it locally or via
  a continuous integration service such as GitLab, GitHub Actions, Jenkins
  or others, it will provide an equivalent featureset to schroot.  Create
  your "source" environment with a *Dockerfile*, then run your builds in
  it.

* Qemu or Bhyve.  If you're running a virtual system, it might be worth
  considering running the entire system in a single process on the
  host system, either in a hypervisor or a full emulator.

* Chroots and jails.  While plain chroots are a step back from what schroot
  offered, the possibility exists.  FreeBSD jails are much more capable
  than chroots and can now provide virtualisation of the network stack as
  well as the filesystem and other system resources.  Several jail
  management tools exist.

* OpenStack, Kubernetes, and other automatable infrastructure-provisioning
  tools.  For applications which required the automated creation of
  longer-lived environments, there are several solutions of varying
  complexity which should be considered.


## History

schroot originated in mid-2005, when the sbuild(1) Debian package builder
needed a means of building packages in a clean build environment, provisioned
with all of the packages required to satisfy the package build dependencies.
Originally called `sbuild-chroot-helper` in its initial proof of concept
implementation, it was quickly renamed to the shorter `schroot` for the
production release.

At the time of writing, easy-to-use container systems were in their infancy
and there was a need for a tool which:

* did not require root access
* would permit a user to create and destroy virtual environments on demand
* provided template environments which could be quickly and efficiently
  cloned

schroot enabled sbuild to run as a normal user (it previously required
root access via `sudo` to run commands in a chroot), and it also removed
the requirement to painstakingly clean up the environment between
package builds [previously breakage of the enviroment was unfortunately
common, requiring manual action to restore a clean environment].

schroot was later extended to support virtualisation of 32-bit x86
desktop applications on amd64, which was popular for a time during the
transition to fully 64-bit systems when legacy 32-bit software was
still required.  It was also extended to permit the use of Qemu to
transparently run a chroot environment for a completely different
hardware architecture such as arm on amd64, or x86 on powerpc.


## Acknowledgements

I would like to personally thank everyone who has contributed to schroot
over the last 17 years, whether that was with feature requests and
suggestions for the design, code contributions and bugfixes, or even
just a few kind words.  Working on schroot and making a useful tool
used for a diverse range of uses was very satisfying and for the most
part quite enjoyable, so thank you to everyone who helped make this
what it was.

Roger Leigh, 11th June 2022
