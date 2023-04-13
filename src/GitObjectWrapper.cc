#include <git2.h>
#include "taskolib/GitObjectWrapper.h"

namespace task {

// free C-type pointer (overload)
void free_libgit_ptr(git_tree* tree)
{
    git_tree_free(tree);
}
void free_libgit_ptr(git_signature* signature)
{
    git_signature_free(signature);
}
void free_libgit_ptr(git_index* index)
{
    git_index_free(index);
}
void free_libgit_ptr(git_repository* repo)
{
    git_repository_free(repo);
}
void free_libgit_ptr(git_remote* remote)
{
    git_remote_free(remote);
}
void free_libgit_ptr(git_commit* commit)
{
    git_commit_free(commit);
}


LibGitPointer<git_repository> repository_open   (const std::string& repo_path)
{
    git_repository *repo;
    if (git_repository_open(&repo, (repo_path).c_str()))
        repo=nullptr;
    
    return LibGitPointer(repo);

}
LibGitPointer<git_repository> repository_init   (const std::string& repo_path, bool is_bare)
{
    git_repository *repo;
    if (git_repository_init(&repo, (repo_path).c_str(), is_bare))
        repo = nullptr;
    return LibGitPointer(repo);
}
LibGitPointer<git_index>      repository_index  (git_repository* repo)
{
    git_index *index;
    if (git_repository_index(&index, repo))
        index = nullptr;
    return LibGitPointer(index);
}
LibGitPointer<git_signature>  signature_default (git_repository* repo)
{
    git_signature *signature;
    if (git_signature_default(&signature, repo))
        signature = nullptr;
    return LibGitPointer(signature);
}
LibGitPointer<git_signature>  signature_new     (const std::string& name, const std::string& email,
                                                  int time, int offset)
{
    git_signature *signature;
    if (git_signature_new(&signature, name.c_str(), email.c_str(), time, offset))
        signature = nullptr;
    return LibGitPointer(signature);
}
LibGitPointer<git_tree>       tree_lookup       (git_repository* repo, git_oid tree_id)
{
    git_tree *tree;
    if (git_tree_lookup(&tree, repo, &tree_id))
        tree = nullptr;
    return LibGitPointer(tree);
}

LibGitPointer<git_remote>     remote_create       (git_repository* repo, const std::string& remote_name, const std::string& url)
{
    git_remote *remote;
    if (git_remote_create(&remote, repo, remote_name.c_str(), url.c_str()))
        remote = nullptr;
    return LibGitPointer(remote);
}

LibGitPointer<git_remote>     remote_lookup       (git_repository* repo, const std::string& remote_name, const std::string& url)
{
    git_remote *remote;
    if (git_remote_lookup(&remote, repo, remote_name.c_str()))
        remote = nullptr;
    return LibGitPointer(remote);
}

}