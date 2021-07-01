using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class 敌人 : MonoBehaviour
{
    public float speed = 3f;
    private Rigidbody2D rbody;

    private Vector2 moveDt;
    public bool isVer;

    //改变方向计时器
    private float changeDerTime = 2f;
    private float changeDerTimelr;

    private Animator anim;

    private bool isFixed;//是否被修复

    public AudioClip fixedClip;
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        rbody = GetComponent<Rigidbody2D>();
        moveDt = isVer?Vector2.up:Vector2.right;
        changeDerTimelr = changeDerTime;
        isFixed = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(isFixed){
            return;
        }
        changeDerTimelr -= Time.deltaTime;
        if(changeDerTimelr < 0){
            moveDt *= -1;
            changeDerTimelr = changeDerTime;
        }
        Vector2 position = rbody.position;
        position.x += moveDt.x * speed * Time.deltaTime;
        position.y += moveDt.y * speed * Time.deltaTime;
        rbody.MovePosition(position);

        anim.SetFloat("moveX", moveDt.x);
        anim.SetFloat("moveY", moveDt.y);
    }

    void OnCollisionEnter2D(Collision2D other)
    {
        角色移动 pc = other.gameObject.GetComponent<角色移动>();
        if (pc!=null)
        {
            if(pc.MyCurrentHealth <= pc.MyMaxHealth)
            {
                pc.ChangeHealth(-3);
                // Destroy(this.gameObject);
            }
            Debug.Log("玩家碰到了敌人！！");
        }
    }

    //敌人被修复
    public void Fixed(){
        isFixed = true;
        AudioManager.instance.AudioPlay(fixedClip);//播放被修复音效
        rbody.simulated = false;
        anim.SetTrigger("胜利");

    }
}
